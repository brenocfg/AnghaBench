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
struct TYPE_3__ {scalar_t__ sigalgcnt; int /*<<< orphan*/  sigalgs; } ;
typedef  TYPE_1__ sig_cb_st ;
typedef  int /*<<< orphan*/  CERT ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_parse_list (char const*,char,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sig_cb ; 
 int tls1_set_raw_sigalgs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 

int tls1_set_sigalgs_list(CERT *c, const char *str, int client)
{
    sig_cb_st sig;
    sig.sigalgcnt = 0;
    if (!CONF_parse_list(str, ':', 1, sig_cb, &sig))
        return 0;
    if (c == NULL)
        return 1;
    return tls1_set_raw_sigalgs(c, sig.sigalgs, sig.sigalgcnt, client);
}