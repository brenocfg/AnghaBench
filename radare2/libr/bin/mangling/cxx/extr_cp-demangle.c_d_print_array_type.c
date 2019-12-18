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
struct d_print_mod {TYPE_1__* mod; int /*<<< orphan*/  printed; struct d_print_mod* next; } ;
struct d_print_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_ARRAY_TYPE ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 int /*<<< orphan*/  d_append_string (struct d_print_info*,char*) ; 
 int /*<<< orphan*/ * d_left (struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_print_mod_list (struct d_print_info*,int,struct d_print_mod*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
d_print_array_type (struct d_print_info *dpi, int options,
                    struct demangle_component *dc,
                    struct d_print_mod *mods)
{
  int need_space;

  need_space = 1;
  if (mods != NULL)
    {
      int need_paren;
      struct d_print_mod *p;

      need_paren = 0;
      for (p = mods; p != NULL; p = p->next)
	{
	  if (! p->printed)
	    {
	      if (p->mod->type == DEMANGLE_COMPONENT_ARRAY_TYPE)
		{
		  need_space = 0;
		  break;
		}
	      else
		{
		  need_paren = 1;
		  need_space = 1;
		  break;
		}
	    }
	}

      if (need_paren)
	d_append_string (dpi, " (");

      d_print_mod_list (dpi, options, mods, 0);

      if (need_paren)
	d_append_char (dpi, ')');
    }

  if (need_space)
    d_append_char (dpi, ' ');

  d_append_char (dpi, '[');

  if (d_left (dc) != NULL)
    d_print_comp (dpi, options, d_left (dc));

  d_append_char (dpi, ']');
}