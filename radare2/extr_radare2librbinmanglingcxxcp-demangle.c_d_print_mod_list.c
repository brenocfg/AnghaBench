#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct demangle_component* sub; scalar_t__ num; } ;
struct TYPE_4__ {TYPE_1__ s_unary_num; } ;
struct demangle_component {scalar_t__ type; TYPE_2__ u; } ;
struct d_print_template {int dummy; } ;
struct d_print_mod {int printed; struct d_print_mod* next; struct demangle_component* mod; struct d_print_template* templates; } ;
struct d_print_info {struct d_print_template* templates; struct d_print_mod* modifiers; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_ARRAY_TYPE ; 
 scalar_t__ DEMANGLE_COMPONENT_DEFAULT_ARG ; 
 scalar_t__ DEMANGLE_COMPONENT_FUNCTION_TYPE ; 
 scalar_t__ DEMANGLE_COMPONENT_LOCAL_NAME ; 
 int DMGL_JAVA ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 int /*<<< orphan*/  d_append_num (struct d_print_info*,scalar_t__) ; 
 int /*<<< orphan*/  d_append_string (struct d_print_info*,char*) ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_array_type (struct d_print_info*,int,struct demangle_component*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_function_type (struct d_print_info*,int,struct demangle_component*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_mod (struct d_print_info*,int,struct demangle_component*) ; 
 scalar_t__ d_print_saw_error (struct d_print_info*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 
 scalar_t__ is_fnqual_component_type (scalar_t__) ; 

__attribute__((used)) static void
d_print_mod_list (struct d_print_info *dpi, int options,
                  struct d_print_mod *mods, int suffix)
{
  struct d_print_template *hold_dpt;

  if (mods == NULL || d_print_saw_error (dpi))
    return;

  if (mods->printed
      || (! suffix
	  && (is_fnqual_component_type (mods->mod->type))))
    {
      d_print_mod_list (dpi, options, mods->next, suffix);
      return;
    }

  mods->printed = 1;

  hold_dpt = dpi->templates;
  dpi->templates = mods->templates;

  if (mods->mod->type == DEMANGLE_COMPONENT_FUNCTION_TYPE)
    {
      d_print_function_type (dpi, options, mods->mod, mods->next);
      dpi->templates = hold_dpt;
      return;
    }
  else if (mods->mod->type == DEMANGLE_COMPONENT_ARRAY_TYPE)
    {
      d_print_array_type (dpi, options, mods->mod, mods->next);
      dpi->templates = hold_dpt;
      return;
    }
  else if (mods->mod->type == DEMANGLE_COMPONENT_LOCAL_NAME)
    {
      struct d_print_mod *hold_modifiers;
      struct demangle_component *dc;

      /* When this is on the modifier stack, we have pulled any
	 qualifiers off the right argument already.  Otherwise, we
	 print it as usual, but don't let the left argument see any
	 modifiers.  */

      hold_modifiers = dpi->modifiers;
      dpi->modifiers = NULL;
      d_print_comp (dpi, options, d_left (mods->mod));
      dpi->modifiers = hold_modifiers;

      if ((options & DMGL_JAVA) == 0)
	d_append_string (dpi, "::");
      else
	d_append_char (dpi, '.');

      dc = d_right (mods->mod);

      if (dc->type == DEMANGLE_COMPONENT_DEFAULT_ARG)
	{
	  d_append_string (dpi, "{default arg#");
	  d_append_num (dpi, dc->u.s_unary_num.num + 1);
	  d_append_string (dpi, "}::");
	  dc = dc->u.s_unary_num.sub;
	}

      while (is_fnqual_component_type (dc->type))
	dc = d_left (dc);

      d_print_comp (dpi, options, dc);

      dpi->templates = hold_dpt;
      return;
    }

  d_print_mod (dpi, options, mods->mod);

  dpi->templates = hold_dpt;

  d_print_mod_list (dpi, options, mods->next, suffix);
}