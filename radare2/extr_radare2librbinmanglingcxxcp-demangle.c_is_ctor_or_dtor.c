#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kind; } ;
struct TYPE_4__ {int kind; } ;
struct TYPE_6__ {TYPE_2__ s_dtor; TYPE_1__ s_ctor; } ;
struct demangle_component {int type; TYPE_3__ u; } ;
struct d_info {int num_comps; int num_subs; void* subs; void* comps; } ;
typedef  enum gnu_v3_dtor_kinds { ____Placeholder_gnu_v3_dtor_kinds } gnu_v3_dtor_kinds ;
typedef  enum gnu_v3_ctor_kinds { ____Placeholder_gnu_v3_ctor_kinds } gnu_v3_ctor_kinds ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_CONST_THIS 138 
#define  DEMANGLE_COMPONENT_CTOR 137 
#define  DEMANGLE_COMPONENT_DTOR 136 
#define  DEMANGLE_COMPONENT_LOCAL_NAME 135 
#define  DEMANGLE_COMPONENT_QUAL_NAME 134 
#define  DEMANGLE_COMPONENT_REFERENCE_THIS 133 
#define  DEMANGLE_COMPONENT_RESTRICT_THIS 132 
#define  DEMANGLE_COMPONENT_RVALUE_REFERENCE_THIS 131 
#define  DEMANGLE_COMPONENT_TEMPLATE 130 
#define  DEMANGLE_COMPONENT_TYPED_NAME 129 
#define  DEMANGLE_COMPONENT_VOLATILE_THIS 128 
 int /*<<< orphan*/  DMGL_GNU_V3 ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  cplus_demangle_init_info (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d_info*) ; 
 struct demangle_component* cplus_demangle_mangled_name (struct d_info*,int) ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
is_ctor_or_dtor (const char *mangled,
                 enum gnu_v3_ctor_kinds *ctor_kind,
                 enum gnu_v3_dtor_kinds *dtor_kind)
{
  struct d_info di;
  struct demangle_component *dc;
  int ret;

  *ctor_kind = (enum gnu_v3_ctor_kinds) 0;
  *dtor_kind = (enum gnu_v3_dtor_kinds) 0;

  cplus_demangle_init_info (mangled, DMGL_GNU_V3, strlen (mangled), &di);

  {
#ifdef CP_DYNAMIC_ARRAYS
    __extension__ struct demangle_component comps[di.num_comps];
    __extension__ struct demangle_component *subs[di.num_subs];

    di.comps = comps;
    di.subs = subs;
#else
    di.comps = alloca (di.num_comps * sizeof (*di.comps));
    di.subs = alloca (di.num_subs * sizeof (*di.subs));
#endif

    dc = cplus_demangle_mangled_name (&di, 1);

    /* Note that because we did not pass DMGL_PARAMS, we don't expect
       to demangle the entire string.  */

    ret = 0;
    while (dc != NULL)
      {
	switch (dc->type)
	  {
	    /* These cannot appear on a constructor or destructor.  */
	  case DEMANGLE_COMPONENT_RESTRICT_THIS:
	  case DEMANGLE_COMPONENT_VOLATILE_THIS:
	  case DEMANGLE_COMPONENT_CONST_THIS:
	  case DEMANGLE_COMPONENT_REFERENCE_THIS:
	  case DEMANGLE_COMPONENT_RVALUE_REFERENCE_THIS:
	  default:
	    dc = NULL;
	    break;
	  case DEMANGLE_COMPONENT_TYPED_NAME:
	  case DEMANGLE_COMPONENT_TEMPLATE:
	    dc = d_left (dc);
	    break;
	  case DEMANGLE_COMPONENT_QUAL_NAME:
	  case DEMANGLE_COMPONENT_LOCAL_NAME:
	    dc = d_right (dc);
	    break;
	  case DEMANGLE_COMPONENT_CTOR:
	    *ctor_kind = dc->u.s_ctor.kind;
	    ret = 1;
	    dc = NULL;
	    break;
	  case DEMANGLE_COMPONENT_DTOR:
	    *dtor_kind = dc->u.s_dtor.kind;
	    ret = 1;
	    dc = NULL;
	    break;
	  }
      }
  }

  return ret;
}