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
struct d_info {char const* s; char const* send; int options; char const* n; int num_comps; size_t num_subs; scalar_t__ is_conversion; scalar_t__ is_expression; scalar_t__ expansion; int /*<<< orphan*/ * last_name; scalar_t__ next_sub; scalar_t__ next_comp; } ;

/* Variables and functions */

void
cplus_demangle_init_info (const char *mangled, int options, size_t len,
                          struct d_info *di)
{
  di->s = mangled;
  di->send = mangled + len;
  di->options = options;

  di->n = mangled;

  /* We can not need more components than twice the number of chars in
     the mangled string.  Most components correspond directly to
     chars, but the ARGLIST types are exceptions.  */
  di->num_comps = 2 * len;
  di->next_comp = 0;

  /* Similarly, we can not need more substitutions than there are
     chars in the mangled string.  */
  di->num_subs = len;
  di->next_sub = 0;

  di->last_name = NULL;

  di->expansion = 0;
  di->is_expression = 0;
  di->is_conversion = 0;
}