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

/* Variables and functions */
 int TOP_NET30 ; 
 int TOP_P2P ; 
 int TOP_SUBNET ; 
 int TOP_UNDEF ; 
 int /*<<< orphan*/  msg (int const,char*) ; 
 scalar_t__ streq (char const*,char*) ; 

int
parse_topology(const char *str, const int msglevel)
{
    if (streq(str, "net30"))
    {
        return TOP_NET30;
    }
    else if (streq(str, "p2p"))
    {
        return TOP_P2P;
    }
    else if (streq(str, "subnet"))
    {
        return TOP_SUBNET;
    }
    else
    {
        msg(msglevel, "--topology must be net30, p2p, or subnet");
        return TOP_UNDEF;
    }
}