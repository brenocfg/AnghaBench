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
struct demangle_component {int d_printing; } ;
struct d_print_info {scalar_t__ recursion; struct d_component_stack* component_stack; } ;
struct d_component_stack {struct d_component_stack* parent; struct demangle_component* dc; } ;

/* Variables and functions */
 scalar_t__ MAX_RECURSION_COUNT ; 
 int /*<<< orphan*/  d_print_comp_inner (struct d_print_info*,int,struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_error (struct d_print_info*) ; 

__attribute__((used)) static void
d_print_comp (struct d_print_info *dpi, int options,
	      struct demangle_component *dc)
{
  struct d_component_stack self;
  if (dc == NULL || dc->d_printing > 1 || dpi->recursion > MAX_RECURSION_COUNT)
    {
      d_print_error (dpi);
      return;
    }

  dc->d_printing++;
  dpi->recursion++;

  self.dc = dc;
  self.parent = dpi->component_stack;
  dpi->component_stack = &self;

  d_print_comp_inner (dpi, options, dc);

  dpi->component_stack = self.parent;
  dc->d_printing--;
  dpi->recursion--;
}