#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_log {int dummy; } ;
struct bstr {int dummy; } ;
struct TYPE_3__ {scalar_t__ priv; } ;
typedef  TYPE_1__ m_option_t ;
typedef  int /*<<< orphan*/  (* m_opt_print_fn ) (struct mp_log*) ;

/* Variables and functions */
 int M_OPT_EXIT ; 
 int /*<<< orphan*/  stub1 (struct mp_log*) ; 

__attribute__((used)) static int parse_print(struct mp_log *log, const m_option_t *opt,
                       struct bstr name, struct bstr param, void *dst)
{
    ((m_opt_print_fn) opt->priv)(log);
    return M_OPT_EXIT;
}