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
struct mp_log {int dummy; } ;
struct bstr {int dummy; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 int M_OPT_INVALID ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*) ; 

__attribute__((used)) static int parse_node(struct mp_log *log, const m_option_t *opt,
                      struct bstr name, struct bstr param, void *dst)
{
    // Maybe use JSON?
    mp_err(log, "option type doesn't accept strings");
    return M_OPT_INVALID;
}