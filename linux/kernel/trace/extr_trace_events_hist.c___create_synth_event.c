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
struct synth_field {int /*<<< orphan*/  devent; } ;
struct synth_event {int /*<<< orphan*/  devent; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct synth_field*) ; 
 int PTR_ERR (struct synth_field*) ; 
 int SYNTH_FIELDS_MAX ; 
 struct synth_field* alloc_synth_event (char const*,int,struct synth_field**) ; 
 int /*<<< orphan*/  dyn_event_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 struct synth_field* find_synth_event (char const*) ; 
 int /*<<< orphan*/  free_synth_event (struct synth_field*) ; 
 int /*<<< orphan*/  free_synth_field (struct synth_field*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct synth_field* parse_synth_field (int,char const**,int*) ; 
 int register_synth_event (struct synth_field*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int __create_synth_event(int argc, const char *name, const char **argv)
{
	struct synth_field *field, *fields[SYNTH_FIELDS_MAX];
	struct synth_event *event = NULL;
	int i, consumed = 0, n_fields = 0, ret = 0;

	/*
	 * Argument syntax:
	 *  - Add synthetic event: <event_name> field[;field] ...
	 *  - Remove synthetic event: !<event_name> field[;field] ...
	 *      where 'field' = type field_name
	 */

	if (name[0] == '\0' || argc < 1)
		return -EINVAL;

	mutex_lock(&event_mutex);

	event = find_synth_event(name);
	if (event) {
		ret = -EEXIST;
		goto out;
	}

	for (i = 0; i < argc - 1; i++) {
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
	ret = register_synth_event(event);
	if (!ret)
		dyn_event_add(&event->devent);
	else
		free_synth_event(event);
 out:
	mutex_unlock(&event_mutex);

	return ret;
 err:
	for (i = 0; i < n_fields; i++)
		free_synth_field(fields[i]);

	goto out;
}