#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int leaf_type; scalar_t__ get_print_type; scalar_t__ get_mlist; scalar_t__ get_index; scalar_t__ get_arglist; scalar_t__ get_this_type; scalar_t__ get_class_type; scalar_t__ get_return_type; scalar_t__ get_utype; scalar_t__ get_vshape; scalar_t__ get_derived; scalar_t__ get_base_type; scalar_t__ get_index_type; scalar_t__ get_element_type; scalar_t__ get_arg_type; scalar_t__ get_members; scalar_t__ get_name_len; scalar_t__ get_val; scalar_t__ get_name; scalar_t__ free_; scalar_t__ is_fwdref; scalar_t__ get_modified_type; } ;
typedef  TYPE_1__ STypeInfo ;

/* Variables and functions */
#define  eLF_ARGLIST 146 
#define  eLF_ARRAY 145 
#define  eLF_BITFIELD 144 
#define  eLF_CLASS 143 
#define  eLF_ENUM 142 
#define  eLF_ENUMERATE 141 
#define  eLF_FIELDLIST 140 
#define  eLF_MEMBER 139 
#define  eLF_METHOD 138 
#define  eLF_METHODLIST 137 
#define  eLF_MFUNCTION 136 
#define  eLF_MODIFIER 135 
#define  eLF_NESTTYPE 134 
#define  eLF_ONEMETHOD 133 
#define  eLF_POINTER 132 
#define  eLF_PROCEDURE 131 
#define  eLF_STRUCTURE 130 
#define  eLF_UNION 129 
#define  eLF_VTSHAPE 128 
 scalar_t__ free_lf_arglist ; 
 scalar_t__ free_lf_array ; 
 scalar_t__ free_lf_class ; 
 scalar_t__ free_lf_enum ; 
 scalar_t__ free_lf_enumerate ; 
 scalar_t__ free_lf_fieldlist ; 
 scalar_t__ free_lf_member ; 
 scalar_t__ free_lf_method ; 
 scalar_t__ free_lf_nesttype ; 
 scalar_t__ free_lf_onemethod ; 
 scalar_t__ free_lf_union ; 
 scalar_t__ free_lf_vtshape ; 
 scalar_t__ get_arglist_print_type ; 
 scalar_t__ get_array_element_type ; 
 scalar_t__ get_array_index_type ; 
 scalar_t__ get_array_name ; 
 scalar_t__ get_array_name_len ; 
 scalar_t__ get_array_print_type ; 
 scalar_t__ get_array_val ; 
 scalar_t__ get_bitfield_base_type ; 
 scalar_t__ get_bitfield_print_type ; 
 scalar_t__ get_class_struct_derived ; 
 scalar_t__ get_class_struct_name ; 
 scalar_t__ get_class_struct_name_len ; 
 scalar_t__ get_class_struct_print_type ; 
 scalar_t__ get_class_struct_val ; 
 scalar_t__ get_class_struct_vshape ; 
 scalar_t__ get_enum_members ; 
 scalar_t__ get_enum_name ; 
 scalar_t__ get_enum_name_len ; 
 scalar_t__ get_enum_print_type ; 
 scalar_t__ get_enum_utype ; 
 scalar_t__ get_enumerate_name ; 
 scalar_t__ get_enumerate_name_len ; 
 scalar_t__ get_enumerate_print_type ; 
 scalar_t__ get_enumerate_val ; 
 scalar_t__ get_fieldlist_members ; 
 scalar_t__ get_fieldlist_print_type ; 
 scalar_t__ get_member_index ; 
 scalar_t__ get_member_name ; 
 scalar_t__ get_member_name_len ; 
 scalar_t__ get_member_print_type ; 
 scalar_t__ get_member_val ; 
 scalar_t__ get_method_mlist ; 
 scalar_t__ get_method_name ; 
 scalar_t__ get_method_name_len ; 
 scalar_t__ get_method_print_type ; 
 scalar_t__ get_mfunction_arglist ; 
 scalar_t__ get_mfunction_class_type ; 
 scalar_t__ get_mfunction_print_type ; 
 scalar_t__ get_mfunction_return_type ; 
 scalar_t__ get_mfunction_this_type ; 
 scalar_t__ get_modifier_modified_type ; 
 scalar_t__ get_modifier_print_type ; 
 scalar_t__ get_nesttype_index ; 
 scalar_t__ get_nesttype_name ; 
 scalar_t__ get_nesttype_name_len ; 
 scalar_t__ get_nesttype_print_type ; 
 scalar_t__ get_onemethod_index ; 
 scalar_t__ get_onemethod_name ; 
 scalar_t__ get_onemethod_name_len ; 
 scalar_t__ get_onemethod_print_type ; 
 scalar_t__ get_onemethod_val ; 
 scalar_t__ get_pointer_print_type ; 
 scalar_t__ get_pointer_utype ; 
 scalar_t__ get_procedure_arglist ; 
 scalar_t__ get_procedure_print_type ; 
 scalar_t__ get_procedure_return_type ; 
 scalar_t__ get_struct_class_members ; 
 scalar_t__ get_union_members ; 
 scalar_t__ get_union_name ; 
 scalar_t__ get_union_name_len ; 
 scalar_t__ get_union_print_type ; 
 scalar_t__ get_union_val ; 
 scalar_t__ get_vtshape_print_type ; 
 scalar_t__ is_struct_class_fwdref ; 
 scalar_t__ is_union_fwdref ; 

__attribute__((used)) static void init_stype_info(STypeInfo *type_info)
{
	type_info->free_ = 0;
	type_info->get_members = 0;
	type_info->get_name = 0;
	type_info->get_val = 0;
	type_info->get_name_len = 0;
	type_info->get_arg_type = 0;
	type_info->get_element_type = 0;
	type_info->get_index_type = 0;
	type_info->get_base_type = 0;
	type_info->get_derived = 0;
	type_info->get_vshape = 0;
	type_info->get_utype = 0;
	type_info->get_return_type = 0;
	type_info->get_class_type = 0;
	type_info->get_this_type = 0;
	type_info->get_arglist = 0;
	type_info->get_index = 0;
	type_info->get_mlist = 0;
	type_info->get_modified_type = 0;
	type_info->is_fwdref = 0;
	type_info->get_print_type = 0;

	switch (type_info->leaf_type) {
	case eLF_FIELDLIST:
		type_info->get_members = get_fieldlist_members;
		type_info->free_ = free_lf_fieldlist;
		type_info->get_print_type = get_fieldlist_print_type;
		break;
	case eLF_ENUM:
		type_info->get_name = get_enum_name;
		type_info->get_name_len = get_enum_name_len;
		type_info->get_members = get_enum_members;
		type_info->get_utype = get_enum_utype;
		type_info->free_ = free_lf_enum;
		type_info->get_print_type = get_enum_print_type;
		break;
	case eLF_CLASS:
	case eLF_STRUCTURE:
		type_info->get_name = get_class_struct_name;
		type_info->get_val = get_class_struct_val; // for structure this is size
		type_info->get_name_len = get_class_struct_name_len;
		type_info->get_members = get_struct_class_members;
		type_info->get_derived = get_class_struct_derived;
		type_info->get_vshape = get_class_struct_vshape;
		type_info->is_fwdref = is_struct_class_fwdref;
		type_info->free_ = free_lf_class;
		type_info->get_print_type = get_class_struct_print_type;
		break;
	case eLF_POINTER:
		type_info->get_utype = get_pointer_utype;
		type_info->get_print_type = get_pointer_print_type;
		break;
	case eLF_ARRAY:
		type_info->get_name = get_array_name;
		type_info->get_val = get_array_val;
		type_info->get_name_len = get_array_name_len;
		type_info->get_element_type = get_array_element_type;
		type_info->get_index_type = get_array_index_type;
		type_info->free_ = free_lf_array;
		type_info->get_print_type = get_array_print_type;
		break;
	case eLF_MODIFIER:
		type_info->get_modified_type = get_modifier_modified_type;
		type_info->get_print_type = get_modifier_print_type;
		break;
	case eLF_ARGLIST:
		type_info->free_ = free_lf_arglist;
		type_info->get_print_type = get_arglist_print_type;
		break;
	case eLF_MFUNCTION:
		type_info->get_return_type = get_mfunction_return_type;
		type_info->get_class_type = get_mfunction_class_type;
		type_info->get_this_type = get_mfunction_this_type;
		type_info->get_arglist = get_mfunction_arglist;
		type_info->get_print_type = get_mfunction_print_type;
		break;
	case eLF_METHODLIST:
		break;
	case eLF_PROCEDURE:
		type_info->get_return_type = get_procedure_return_type;
		type_info->get_arglist = get_procedure_arglist;
		type_info->get_print_type = get_procedure_print_type;
		break;
	case eLF_UNION:
		type_info->get_name = get_union_name;
		type_info->get_val = get_union_val;
		type_info->get_name_len = get_union_name_len;
		type_info->get_members = get_union_members;
		type_info->is_fwdref = is_union_fwdref;
		type_info->free_ = free_lf_union;
		type_info->get_print_type = get_union_print_type;
		break;
	case eLF_BITFIELD:
		type_info->get_base_type = get_bitfield_base_type;
		type_info->get_print_type = get_bitfield_print_type;
		break;
	case eLF_VTSHAPE:
		type_info->free_ = free_lf_vtshape;
		type_info->get_print_type = get_vtshape_print_type;
		break;
	case eLF_ENUMERATE:
		type_info->get_name = get_enumerate_name;
		type_info->get_val = get_enumerate_val;
		type_info->get_name_len = get_enumerate_name_len;
		type_info->free_ = free_lf_enumerate;
		type_info->get_print_type = get_enumerate_print_type;
		break;
	case eLF_NESTTYPE:
		type_info->get_name = get_nesttype_name;
		type_info->get_name_len = get_nesttype_name_len;
		type_info->get_index = get_nesttype_index;
		type_info->free_ = free_lf_nesttype;
		type_info->get_print_type = get_nesttype_print_type;
		break;
	case eLF_METHOD:
		type_info->get_name = get_method_name;
		type_info->get_name_len = get_method_name_len;
		type_info->get_mlist = get_method_mlist;
		type_info->free_ = free_lf_method;
		type_info->get_print_type = get_method_print_type;
		break;
	case eLF_MEMBER:
		type_info->get_name = get_member_name;
		type_info->get_val = get_member_val;
		type_info->get_name_len = get_member_name_len;
		type_info->get_index = get_member_index;
		type_info->free_ = free_lf_member;
		type_info->get_print_type = get_member_print_type;
		break;
	case eLF_ONEMETHOD:
		type_info->get_name = get_onemethod_name;
		type_info->get_name_len = get_onemethod_name_len;
		type_info->get_val = get_onemethod_val;
		type_info->get_index = get_onemethod_index;
		type_info->free_ = free_lf_onemethod;
		type_info->get_print_type = get_onemethod_print_type;
		break;
	default:
//		printf("init_stype_info(): unknown type for init\n");
		type_info->get_name = 0;
		type_info->get_val = 0;
		type_info->get_name_len = 0;
		type_info->get_members = 0;
		type_info->get_arg_type = 0;
		type_info->get_element_type = 0;
		type_info->get_index_type = 0;
		type_info->get_base_type = 0;
		type_info->get_derived = 0;
		type_info->get_vshape = 0;
		type_info->get_utype = 0;
		type_info->get_return_type = 0;
		type_info->get_class_type = 0;
		type_info->get_this_type = 0;
		type_info->get_arglist = 0;
		type_info->get_index = 0;
		type_info->get_mlist = 0;
		type_info->get_print_type = 0;
		break;
	}
}