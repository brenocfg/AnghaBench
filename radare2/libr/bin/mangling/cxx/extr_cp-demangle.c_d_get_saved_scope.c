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
struct d_saved_scope {struct demangle_component const* container; } ;
struct d_print_info {int next_saved_scope; struct d_saved_scope* saved_scopes; } ;

/* Variables and functions */

__attribute__((used)) static struct d_saved_scope *
d_get_saved_scope (struct d_print_info *dpi,
		   const struct demangle_component *container)
{
  int i;

  for (i = 0; i < dpi->next_saved_scope; i++)
    if (dpi->saved_scopes[i].container == container)
      return &dpi->saved_scopes[i];

  return NULL;
}