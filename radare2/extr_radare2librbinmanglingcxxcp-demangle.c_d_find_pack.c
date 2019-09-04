#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct demangle_component* name; } ;
struct TYPE_5__ {struct demangle_component* name; } ;
struct TYPE_8__ {struct demangle_component* name; } ;
struct TYPE_7__ {TYPE_2__ s_dtor; TYPE_1__ s_ctor; TYPE_4__ s_extended_operator; } ;
struct demangle_component {int type; TYPE_3__ u; } ;
struct d_print_info {int dummy; } ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_BUILTIN_TYPE 144 
#define  DEMANGLE_COMPONENT_CHARACTER 143 
#define  DEMANGLE_COMPONENT_CTOR 142 
#define  DEMANGLE_COMPONENT_DEFAULT_ARG 141 
#define  DEMANGLE_COMPONENT_DTOR 140 
#define  DEMANGLE_COMPONENT_EXTENDED_OPERATOR 139 
#define  DEMANGLE_COMPONENT_FIXED_TYPE 138 
#define  DEMANGLE_COMPONENT_FUNCTION_PARAM 137 
#define  DEMANGLE_COMPONENT_LAMBDA 136 
#define  DEMANGLE_COMPONENT_NAME 135 
#define  DEMANGLE_COMPONENT_NUMBER 134 
#define  DEMANGLE_COMPONENT_OPERATOR 133 
#define  DEMANGLE_COMPONENT_PACK_EXPANSION 132 
#define  DEMANGLE_COMPONENT_SUB_STD 131 
#define  DEMANGLE_COMPONENT_TAGGED_NAME 130 
 int DEMANGLE_COMPONENT_TEMPLATE_ARGLIST ; 
#define  DEMANGLE_COMPONENT_TEMPLATE_PARAM 129 
#define  DEMANGLE_COMPONENT_UNNAMED_TYPE 128 
 struct demangle_component* d_left (struct demangle_component const*) ; 
 struct demangle_component* d_lookup_template_argument (struct d_print_info*,struct demangle_component const*) ; 
 struct demangle_component* d_right (struct demangle_component const*) ; 

__attribute__((used)) static struct demangle_component *
d_find_pack (struct d_print_info *dpi,
	     const struct demangle_component *dc)
{
  struct demangle_component *a;
  if (dc == NULL)
    return NULL;

  switch (dc->type)
    {
    case DEMANGLE_COMPONENT_TEMPLATE_PARAM:
      a = d_lookup_template_argument (dpi, dc);
      if (a && a->type == DEMANGLE_COMPONENT_TEMPLATE_ARGLIST)
	return a;
      return NULL;

    case DEMANGLE_COMPONENT_PACK_EXPANSION:
      return NULL;
      
    case DEMANGLE_COMPONENT_LAMBDA:
    case DEMANGLE_COMPONENT_NAME:
    case DEMANGLE_COMPONENT_TAGGED_NAME:
    case DEMANGLE_COMPONENT_OPERATOR:
    case DEMANGLE_COMPONENT_BUILTIN_TYPE:
    case DEMANGLE_COMPONENT_SUB_STD:
    case DEMANGLE_COMPONENT_CHARACTER:
    case DEMANGLE_COMPONENT_FUNCTION_PARAM:
    case DEMANGLE_COMPONENT_UNNAMED_TYPE:
    case DEMANGLE_COMPONENT_FIXED_TYPE:
    case DEMANGLE_COMPONENT_DEFAULT_ARG:
    case DEMANGLE_COMPONENT_NUMBER:
      return NULL;

    case DEMANGLE_COMPONENT_EXTENDED_OPERATOR:
      return d_find_pack (dpi, dc->u.s_extended_operator.name);
    case DEMANGLE_COMPONENT_CTOR:
      return d_find_pack (dpi, dc->u.s_ctor.name);
    case DEMANGLE_COMPONENT_DTOR:
      return d_find_pack (dpi, dc->u.s_dtor.name);

    default:
      a = d_find_pack (dpi, d_left (dc));
      if (a)
	return a;
      return d_find_pack (dpi, d_right (dc));
    }
}