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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int const M_FATAL ; 
 unsigned int const M_USAGE_SMALL ; 
 int /*<<< orphan*/  OPENVPN_EXIT_STATUS_CANNOT_OPEN_DEBUG_FILE ; 
 int /*<<< orphan*/ * default_err ; 
 int /*<<< orphan*/ * default_out ; 
 int /*<<< orphan*/ * msgfp ; 
 int /*<<< orphan*/  openvpn_exit (int /*<<< orphan*/ ) ; 

FILE *
msg_fp(const unsigned int flags)
{
    FILE *fp = msgfp;
    if (!fp)
    {
        fp = (flags & (M_FATAL|M_USAGE_SMALL)) ? default_err : default_out;
    }
    if (!fp)
    {
        openvpn_exit(OPENVPN_EXIT_STATUS_CANNOT_OPEN_DEBUG_FILE); /* exit point */
    }
    return fp;
}