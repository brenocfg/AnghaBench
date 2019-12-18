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
 int IP_PMTUDISC_DO ; 
 int IP_PMTUDISC_DONT ; 
 int IP_PMTUDISC_WANT ; 
 int /*<<< orphan*/  MTUDISC_NOT_SUPPORTED_MSG ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int
translate_mtu_discover_type_name(const char *name)
{
#if defined(IP_PMTUDISC_DONT) && defined(IP_PMTUDISC_WANT) && defined(IP_PMTUDISC_DO)
    if (!strcmp(name, "yes"))
    {
        return IP_PMTUDISC_DO;
    }
    if (!strcmp(name, "maybe"))
    {
        return IP_PMTUDISC_WANT;
    }
    if (!strcmp(name, "no"))
    {
        return IP_PMTUDISC_DONT;
    }
    msg(M_FATAL,
        "invalid --mtu-disc type: '%s' -- valid types are 'yes', 'maybe', or 'no'",
        name);
#else  /* if defined(IP_PMTUDISC_DONT) && defined(IP_PMTUDISC_WANT) && defined(IP_PMTUDISC_DO) */
    msg(M_FATAL, MTUDISC_NOT_SUPPORTED_MSG);
#endif
    return -1;                  /* NOTREACHED */
}