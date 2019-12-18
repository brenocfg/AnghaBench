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
struct lwan_var_descriptor {int dummy; } ;
struct lwan_tpl {int dummy; } ;
typedef  enum lwan_tpl_flag { ____Placeholder_lwan_tpl_flag } lwan_tpl_flag ;

/* Variables and functions */
 struct lwan_tpl* calloc (int,int) ; 
 int /*<<< orphan*/  dump_program (struct lwan_tpl*) ; 
 int /*<<< orphan*/  lwan_tpl_free (struct lwan_tpl*) ; 
 scalar_t__ parse_string (struct lwan_tpl*,char const*,struct lwan_var_descriptor const*,int) ; 

struct lwan_tpl *
lwan_tpl_compile_string_full(const char *string,
                             const struct lwan_var_descriptor *descriptor,
                             enum lwan_tpl_flag flags)
{
    struct lwan_tpl *tpl;

    tpl = calloc(1, sizeof(*tpl));
    if (tpl) {
        if (parse_string(tpl, string, descriptor, flags)) {
#if !defined(NDEBUG) && defined(TEMPLATE_DEBUG)
            dump_program(tpl);
#endif

            return tpl;
        }

        lwan_tpl_free(tpl);
    }

    return NULL;
}