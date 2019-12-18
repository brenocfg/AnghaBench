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
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  cs_gethostbyname ; 
 scalar_t__ winsock_initialized ; 

void netconn_unload( void )
{
#ifndef HAVE_GETADDRINFO
    DeleteCriticalSection(&cs_gethostbyname);
#endif
#ifdef __REACTOS__
    if(winsock_initialized)
        WSACleanup();
#endif
}