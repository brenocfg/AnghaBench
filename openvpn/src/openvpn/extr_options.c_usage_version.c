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
 int /*<<< orphan*/  CONFIGURE_DEFINES ; 
 int /*<<< orphan*/  CONFIGURE_SPECIAL_BUILD ; 
 int M_INFO ; 
 int M_NOPREFIX ; 
 int /*<<< orphan*/  OPENVPN_EXIT_STATUS_USAGE ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  openvpn_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_library_versions (int) ; 
 int /*<<< orphan*/  show_windows_version (int) ; 
 int /*<<< orphan*/  title_string ; 

__attribute__((used)) static void
usage_version(void)
{
    msg(M_INFO|M_NOPREFIX, "%s", title_string);
    show_library_versions( M_INFO|M_NOPREFIX );
#ifdef _WIN32
    show_windows_version( M_INFO|M_NOPREFIX );
#endif
    msg(M_INFO|M_NOPREFIX, "Originally developed by James Yonan");
    msg(M_INFO|M_NOPREFIX, "Copyright (C) 2002-2018 OpenVPN Inc <sales@openvpn.net>");
#ifndef ENABLE_SMALL
#ifdef CONFIGURE_DEFINES
    msg(M_INFO|M_NOPREFIX, "Compile time defines: %s", CONFIGURE_DEFINES);
#endif
#ifdef CONFIGURE_SPECIAL_BUILD
    msg(M_INFO|M_NOPREFIX, "special build: %s", CONFIGURE_SPECIAL_BUILD);
#endif
#endif
    openvpn_exit(OPENVPN_EXIT_STATUS_USAGE); /* exit point */
}