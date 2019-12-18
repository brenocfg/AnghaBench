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
struct parse_state {int error; int /*<<< orphan*/  arg; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_FATAL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_strerror (int) ; 
 int split_opt_silent (struct parse_state*) ; 

__attribute__((used)) static bool split_opt(struct parse_state *p)
{
    int r = split_opt_silent(p);
    if (r >= 0)
        return r == 0;
    p->error = true;

    MP_FATAL(p->config, "Error parsing commandline option %.*s: %s\n",
             BSTR_P(p->arg), m_option_strerror(r));
    return false;
}