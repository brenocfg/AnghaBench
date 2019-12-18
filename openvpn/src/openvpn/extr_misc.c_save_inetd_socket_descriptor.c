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
 int /*<<< orphan*/  INETD_SOCKET_DESCRIPTOR ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetd_socket_descriptor ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_std_files_to_null (int) ; 

void
save_inetd_socket_descriptor(void)
{
    inetd_socket_descriptor = INETD_SOCKET_DESCRIPTOR;
#if defined(HAVE_DUP) && defined(HAVE_DUP2)
    /* use handle passed by inetd/xinetd */
    if ((inetd_socket_descriptor = dup(INETD_SOCKET_DESCRIPTOR)) < 0)
    {
        msg(M_ERR, "INETD_SOCKET_DESCRIPTOR dup(%d) failed", INETD_SOCKET_DESCRIPTOR);
    }
    set_std_files_to_null(true);
#endif
}