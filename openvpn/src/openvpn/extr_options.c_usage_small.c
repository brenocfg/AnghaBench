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
 int M_NOPREFIX ; 
 int M_WARN ; 
 int /*<<< orphan*/  OPENVPN_EXIT_STATUS_USAGE ; 
 int /*<<< orphan*/  msg (int,char*) ; 
 int /*<<< orphan*/  openvpn_exit (int /*<<< orphan*/ ) ; 

void
usage_small(void)
{
    msg(M_WARN|M_NOPREFIX, "Use --help for more information.");
    openvpn_exit(OPENVPN_EXIT_STATUS_USAGE); /* exit point */
}