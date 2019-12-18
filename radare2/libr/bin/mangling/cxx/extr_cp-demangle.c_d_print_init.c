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
struct d_print_info {char last_char; int /*<<< orphan*/ * current_template; int /*<<< orphan*/  num_saved_scopes; int /*<<< orphan*/  num_copy_templates; scalar_t__ next_copy_template; int /*<<< orphan*/ * copy_templates; scalar_t__ next_saved_scope; int /*<<< orphan*/ * saved_scopes; int /*<<< orphan*/ * component_stack; scalar_t__ is_lambda_arg; scalar_t__ recursion; scalar_t__ demangle_failure; void* opaque; int /*<<< orphan*/  callback; scalar_t__ flush_count; scalar_t__ pack_index; int /*<<< orphan*/ * modifiers; int /*<<< orphan*/ * templates; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  demangle_callbackref ;

/* Variables and functions */
 int /*<<< orphan*/  d_count_templates_scopes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct demangle_component const*) ; 

__attribute__((used)) static void
d_print_init (struct d_print_info *dpi, demangle_callbackref callback,
	      void *opaque, const struct demangle_component *dc)
{
  dpi->len = 0;
  dpi->last_char = '\0';
  dpi->templates = NULL;
  dpi->modifiers = NULL;
  dpi->pack_index = 0;
  dpi->flush_count = 0;

  dpi->callback = callback;
  dpi->opaque = opaque;

  dpi->demangle_failure = 0;
  dpi->recursion = 0;
  dpi->is_lambda_arg = 0;

  dpi->component_stack = NULL;

  dpi->saved_scopes = NULL;
  dpi->next_saved_scope = 0;
  dpi->num_saved_scopes = 0;

  dpi->copy_templates = NULL;
  dpi->next_copy_template = 0;
  dpi->num_copy_templates = 0;

  d_count_templates_scopes (&dpi->num_copy_templates,
			    &dpi->num_saved_scopes, dc);
  dpi->num_copy_templates *= dpi->num_saved_scopes;

  dpi->current_template = NULL;
}