#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct synth_field {int /*<<< orphan*/  list; scalar_t__ ref; } ;
struct synth_event {int /*<<< orphan*/  list; scalar_t__ ref; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct synth_field*) ; 
 int PTR_ERR (struct synth_field*) ; 
 int SYNTH_FIELDS_MAX ; 
 int /*<<< orphan*/  add_or_delete_synth_event (struct synth_field*,int) ; 
 struct synth_field* alloc_synth_event (char*,int,struct synth_field**) ; 
 struct synth_field* find_synth_event (char*) ; 
 int /*<<< orphan*/  free_synth_event (struct synth_field*) ; 
 int /*<<< orphan*/  free_synth_field (struct synth_field*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct synth_field* parse_synth_field (int,char**,int*) ; 
 int register_synth_event (struct synth_field*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  synth_event_mutex ; 
 int unregister_synth_event (struct synth_field*) ; 

__attribute__((used)) static int create_synth_event(int argc, char **argv)
{
	struct synth_field *field, *fields[SYNTH_FIELDS_MAX];
	struct synth_event *event = NULL;
	bool delete_event = false;
	int i, consumed = 0, n_fields = 0, ret = 0;
	char *name;

	mutex_lock(&synth_event_mutex);

	/*
	 * Argument syntax:
	 *  - Add synthetic event: <event_name> field[;field] ...
	 *  - Remove synthetic event: !<event_name> field[;field] ...
	 *      where 'field' = type field_name
	 */
	if (argc < 1) {
		ret = -EINVAL;
		goto out;
	}

	name = argv[0];
	if (name[0] == '!') {
		delete_event = true;
		name++;
	}

	event = find_synth_event(name);
	if (event) {
		if (delete_event) {
			if (event->ref) {
				event = NULL;
				ret = -EBUSY;
				goto out;
			}
			list_del(&event->list);
			goto out;
		}
		event = NULL;
		ret = -EEXIST;
		goto out;
	} else if (delete_event) {
		ret = -ENOENT;
		goto out;
	}

	if (argc < 2) {
		ret = -EINVAL;
		goto out;
	}

	for (i = 1; i < argc - 1; i++) {
		if (strcmp(argv[i], ";") == 0)
			continue;
		if (n_fields == SYNTH_FIELDS_MAX) {
			ret = -EINVAL;
			goto err;
		}

		field = parse_synth_field(argc - i, &argv[i], &consumed);
		if (IS_ERR(field)) {
			ret = PTR_ERR(field);
			goto err;
		}
		fields[n_fields++] = field;
		i += consumed - 1;
	}

	if (i < argc && strcmp(argv[i], ";") != 0) {
		ret = -EINVAL;
		goto err;
	}

	event = alloc_synth_event(name, n_fields, fields);
	if (IS_ERR(event)) {
		ret = PTR_ERR(event);
		event = NULL;
		goto err;
	}
 out:
	mutex_unlock(&synth_event_mutex);

	if (event) {
		if (delete_event) {
			ret = unregister_synth_event(event);
			add_or_delete_synth_event(event, !ret);
		} else {
			ret = register_synth_event(event);
			add_or_delete_synth_event(event, ret);
		}
	}

	return ret;
 err:
	mutex_unlock(&synth_event_mutex);

	for (i = 0; i < n_fields; i++)
		free_synth_field(fields[i]);
	free_synth_event(event);

	return ret;
}