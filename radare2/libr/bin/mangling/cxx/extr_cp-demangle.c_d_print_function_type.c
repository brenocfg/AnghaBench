#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct demangle_component {int dummy; } ;
struct d_print_mod {TYPE_1__* mod; scalar_t__ printed; struct d_print_mod* next; } ;
struct d_print_info {struct d_print_mod* modifiers; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_COMPLEX 137 
#define  DEMANGLE_COMPONENT_CONST 136 
#define  DEMANGLE_COMPONENT_IMAGINARY 135 
#define  DEMANGLE_COMPONENT_POINTER 134 
#define  DEMANGLE_COMPONENT_PTRMEM_TYPE 133 
#define  DEMANGLE_COMPONENT_REFERENCE 132 
#define  DEMANGLE_COMPONENT_RESTRICT 131 
#define  DEMANGLE_COMPONENT_RVALUE_REFERENCE 130 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL 129 
#define  DEMANGLE_COMPONENT_VOLATILE 128 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 char d_last_char (struct d_print_info*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_print_mod_list (struct d_print_info*,int,struct d_print_mod*,int) ; 
 int /*<<< orphan*/ * d_right (struct demangle_component*) ; 

__attribute__((used)) static void
d_print_function_type (struct d_print_info *dpi, int options,
                       struct demangle_component *dc,
                       struct d_print_mod *mods)
{
  int need_paren;
  int need_space;
  struct d_print_mod *p;
  struct d_print_mod *hold_modifiers;

  need_paren = 0;
  need_space = 0;
  for (p = mods; p != NULL; p = p->next)
    {
      if (p->printed)
	break;

      switch (p->mod->type)
	{
	case DEMANGLE_COMPONENT_POINTER:
	case DEMANGLE_COMPONENT_REFERENCE:
	case DEMANGLE_COMPONENT_RVALUE_REFERENCE:
	  need_paren = 1;
	  break;
	case DEMANGLE_COMPONENT_RESTRICT:
	case DEMANGLE_COMPONENT_VOLATILE:
	case DEMANGLE_COMPONENT_CONST:
	case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
	case DEMANGLE_COMPONENT_COMPLEX:
	case DEMANGLE_COMPONENT_IMAGINARY:
	case DEMANGLE_COMPONENT_PTRMEM_TYPE:
	  need_space = 1;
	  need_paren = 1;
	  break;
	FNQUAL_COMPONENT_CASE:
	  break;
	default:
	  break;
	}
      if (need_paren)
	break;
    }

  if (need_paren)
    {
      if (! need_space)
	{
	  if (d_last_char (dpi) != '('
	      && d_last_char (dpi) != '*')
	    need_space = 1;
	}
      if (need_space && d_last_char (dpi) != ' ')
	d_append_char (dpi, ' ');
      d_append_char (dpi, '(');
    }

  hold_modifiers = dpi->modifiers;
  dpi->modifiers = NULL;

  d_print_mod_list (dpi, options, mods, 0);

  if (need_paren)
    d_append_char (dpi, ')');

  d_append_char (dpi, '(');

  if (d_right (dc) != NULL)
    d_print_comp (dpi, options, d_right (dc));

  d_append_char (dpi, ')');

  d_print_mod_list (dpi, options, mods, 1);

  dpi->modifiers = hold_modifiers;
}