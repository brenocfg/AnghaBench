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
struct synth_field {char* type; int is_string; int /*<<< orphan*/  is_signed; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct synth_field* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_synth_field (struct synth_field*) ; 
 int /*<<< orphan*/  kmemdup_nul (char const*,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ synth_field_is_string (char*) ; 
 int /*<<< orphan*/  synth_field_signed (char*) ; 
 int /*<<< orphan*/  synth_field_size (char*) ; 

__attribute__((used)) static struct synth_field *parse_synth_field(int argc, const char **argv,
					     int *consumed)
{
	struct synth_field *field;
	const char *prefix = NULL, *field_type = argv[0], *field_name, *array;
	int len, ret = 0;

	if (field_type[0] == ';')
		field_type++;

	if (!strcmp(field_type, "unsigned")) {
		if (argc < 3)
			return ERR_PTR(-EINVAL);
		prefix = "unsigned ";
		field_type = argv[1];
		field_name = argv[2];
		*consumed = 3;
	} else {
		field_name = argv[1];
		*consumed = 2;
	}

	field = kzalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		return ERR_PTR(-ENOMEM);

	len = strlen(field_name);
	array = strchr(field_name, '[');
	if (array)
		len -= strlen(array);
	else if (field_name[len - 1] == ';')
		len--;

	field->name = kmemdup_nul(field_name, len, GFP_KERNEL);
	if (!field->name) {
		ret = -ENOMEM;
		goto free;
	}

	if (field_type[0] == ';')
		field_type++;
	len = strlen(field_type) + 1;
	if (array)
		len += strlen(array);
	if (prefix)
		len += strlen(prefix);

	field->type = kzalloc(len, GFP_KERNEL);
	if (!field->type) {
		ret = -ENOMEM;
		goto free;
	}
	if (prefix)
		strcat(field->type, prefix);
	strcat(field->type, field_type);
	if (array) {
		strcat(field->type, array);
		if (field->type[len - 1] == ';')
			field->type[len - 1] = '\0';
	}

	field->size = synth_field_size(field->type);
	if (!field->size) {
		ret = -EINVAL;
		goto free;
	}

	if (synth_field_is_string(field->type))
		field->is_string = true;

	field->is_signed = synth_field_signed(field->type);

 out:
	return field;
 free:
	free_synth_field(field);
	field = ERR_PTR(ret);
	goto out;
}