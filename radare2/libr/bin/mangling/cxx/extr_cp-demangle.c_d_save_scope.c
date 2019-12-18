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
struct demangle_component {int dummy; } ;
struct d_saved_scope {struct d_print_template* templates; struct demangle_component const* container; } ;
struct d_print_template {struct d_print_template* next; int /*<<< orphan*/  template_decl; } ;
struct d_print_info {size_t next_saved_scope; size_t num_saved_scopes; size_t next_copy_template; size_t num_copy_templates; struct d_print_template* copy_templates; struct d_print_template* templates; struct d_saved_scope* saved_scopes; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_print_error (struct d_print_info*) ; 

__attribute__((used)) static void
d_save_scope (struct d_print_info *dpi,
	      const struct demangle_component *container)
{
  struct d_saved_scope *scope;
  struct d_print_template *src, **link;

  if (dpi->next_saved_scope >= dpi->num_saved_scopes)
    {
      d_print_error (dpi);
      return;
    }
  scope = &dpi->saved_scopes[dpi->next_saved_scope];
  dpi->next_saved_scope++;

  scope->container = container;
  link = &scope->templates;

  for (src = dpi->templates; src != NULL; src = src->next)
    {
      struct d_print_template *dst;

      if (dpi->next_copy_template >= dpi->num_copy_templates)
	{
	  d_print_error (dpi);
	  return;
	}
      dst = &dpi->copy_templates[dpi->next_copy_template];
      dpi->next_copy_template++;

      dst->template_decl = src->template_decl;
      *link = dst;
      link = &dst->next;
    }

  *link = NULL;
}