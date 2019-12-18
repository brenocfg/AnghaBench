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
struct probe_trace_arg_ref {int offset; int user_access; struct probe_trace_arg_ref* next; } ;
struct perf_probe_arg_field {char* name; int index; struct perf_probe_arg_field* next; scalar_t__ ref; } ;
typedef  scalar_t__ Dwarf_Word ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DW_TAG_array_type ; 
 int DW_TAG_pointer_type ; 
 int DW_TAG_structure_type ; 
 int DW_TAG_union_type ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int /*<<< orphan*/ * die_find_member (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int die_get_data_member_location (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * die_get_real_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dwarf_bytesize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_dieoffset (int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,char const*) ; 
 int /*<<< orphan*/  pr_debug2 (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 struct probe_trace_arg_ref* zalloc (int) ; 

__attribute__((used)) static int convert_variable_fields(Dwarf_Die *vr_die, const char *varname,
				    struct perf_probe_arg_field *field,
				    struct probe_trace_arg_ref **ref_ptr,
				    Dwarf_Die *die_mem, bool user_access)
{
	struct probe_trace_arg_ref *ref = *ref_ptr;
	Dwarf_Die type;
	Dwarf_Word offs;
	int ret, tag;

	pr_debug("converting %s in %s\n", field->name, varname);
	if (die_get_real_type(vr_die, &type) == NULL) {
		pr_warning("Failed to get the type of %s.\n", varname);
		return -ENOENT;
	}
	pr_debug2("Var real type: %s (%x)\n", dwarf_diename(&type),
		  (unsigned)dwarf_dieoffset(&type));
	tag = dwarf_tag(&type);

	if (field->name[0] == '[' &&
	    (tag == DW_TAG_array_type || tag == DW_TAG_pointer_type)) {
		/* Save original type for next field or type */
		memcpy(die_mem, &type, sizeof(*die_mem));
		/* Get the type of this array */
		if (die_get_real_type(&type, &type) == NULL) {
			pr_warning("Failed to get the type of %s.\n", varname);
			return -ENOENT;
		}
		pr_debug2("Array real type: %s (%x)\n", dwarf_diename(&type),
			 (unsigned)dwarf_dieoffset(&type));
		if (tag == DW_TAG_pointer_type) {
			ref = zalloc(sizeof(struct probe_trace_arg_ref));
			if (ref == NULL)
				return -ENOMEM;
			if (*ref_ptr)
				(*ref_ptr)->next = ref;
			else
				*ref_ptr = ref;
		}
		ref->offset += dwarf_bytesize(&type) * field->index;
		ref->user_access = user_access;
		goto next;
	} else if (tag == DW_TAG_pointer_type) {
		/* Check the pointer and dereference */
		if (!field->ref) {
			pr_err("Semantic error: %s must be referred by '->'\n",
			       field->name);
			return -EINVAL;
		}
		/* Get the type pointed by this pointer */
		if (die_get_real_type(&type, &type) == NULL) {
			pr_warning("Failed to get the type of %s.\n", varname);
			return -ENOENT;
		}
		/* Verify it is a data structure  */
		tag = dwarf_tag(&type);
		if (tag != DW_TAG_structure_type && tag != DW_TAG_union_type) {
			pr_warning("%s is not a data structure nor a union.\n",
				   varname);
			return -EINVAL;
		}

		ref = zalloc(sizeof(struct probe_trace_arg_ref));
		if (ref == NULL)
			return -ENOMEM;
		if (*ref_ptr)
			(*ref_ptr)->next = ref;
		else
			*ref_ptr = ref;
	} else {
		/* Verify it is a data structure  */
		if (tag != DW_TAG_structure_type && tag != DW_TAG_union_type) {
			pr_warning("%s is not a data structure nor a union.\n",
				   varname);
			return -EINVAL;
		}
		if (field->name[0] == '[') {
			pr_err("Semantic error: %s is not a pointer"
			       " nor array.\n", varname);
			return -EINVAL;
		}
		/* While prcessing unnamed field, we don't care about this */
		if (field->ref && dwarf_diename(vr_die)) {
			pr_err("Semantic error: %s must be referred by '.'\n",
			       field->name);
			return -EINVAL;
		}
		if (!ref) {
			pr_warning("Structure on a register is not "
				   "supported yet.\n");
			return -ENOTSUP;
		}
	}

	if (die_find_member(&type, field->name, die_mem) == NULL) {
		pr_warning("%s(type:%s) has no member %s.\n", varname,
			   dwarf_diename(&type), field->name);
		return -EINVAL;
	}

	/* Get the offset of the field */
	if (tag == DW_TAG_union_type) {
		offs = 0;
	} else {
		ret = die_get_data_member_location(die_mem, &offs);
		if (ret < 0) {
			pr_warning("Failed to get the offset of %s.\n",
				   field->name);
			return ret;
		}
	}
	ref->offset += (long)offs;
	ref->user_access = user_access;

	/* If this member is unnamed, we need to reuse this field */
	if (!dwarf_diename(die_mem))
		return convert_variable_fields(die_mem, varname, field,
						&ref, die_mem, user_access);

next:
	/* Converting next field */
	if (field->next)
		return convert_variable_fields(die_mem, field->name,
				field->next, &ref, die_mem, user_access);
	else
		return 0;
}