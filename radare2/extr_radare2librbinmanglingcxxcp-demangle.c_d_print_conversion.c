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
struct demangle_component {scalar_t__ type; } ;
struct d_print_template {struct d_print_template* next; int /*<<< orphan*/ * template_decl; int /*<<< orphan*/  member_0; } ;
struct d_print_info {struct d_print_template* templates; int /*<<< orphan*/ * current_template; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_TEMPLATE ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 char d_last_char (struct d_print_info*) ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,int,struct demangle_component*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 

__attribute__((used)) static void
d_print_conversion (struct d_print_info *dpi, int options,
		    struct demangle_component *dc)
{
  struct d_print_template dpt = {0};

  /* For a conversion operator, we need the template parameters from
     the enclosing template in scope for processing the type.  */
  if (dpi->current_template != NULL)
    {
      dpt.next = dpi->templates;
      dpi->templates = &dpt;
      dpt.template_decl = dpi->current_template;
    }

  if (d_left (dc)->type != DEMANGLE_COMPONENT_TEMPLATE)
    {
      d_print_comp (dpi, options, d_left (dc));
      if (dpi->current_template != NULL)
	dpi->templates = dpt.next;
    }
  else
    {
      d_print_comp (dpi, options, d_left (d_left (dc)));

      /* For a templated cast operator, we need to remove the template
	 parameters from scope after printing the operator name,
	 so we need to handle the template printing here.  */
      if (dpi->current_template != NULL)
	dpi->templates = dpt.next;

      if (d_last_char (dpi) == '<')
	d_append_char (dpi, ' ');
      d_append_char (dpi, '<');
      d_print_comp (dpi, options, d_right (d_left (dc)));
      /* Avoid generating two consecutive '>' characters, to avoid
	 the C++ syntactic ambiguity.  */
      if (d_last_char (dpi) == '>')
	d_append_char (dpi, ' ');
      d_append_char (dpi, '>');
    }
}