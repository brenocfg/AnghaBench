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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int pgwin32_noblock ; 
 int /*<<< orphan*/  recv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
secure_raw_read(Port *port, void *ptr, size_t len)
{
	ssize_t		n;

	/*
	 * Try to read from the socket without blocking. If it succeeds we're
	 * done, otherwise we'll wait for the socket using the latch mechanism.
	 */
#ifdef WIN32
	pgwin32_noblock = true;
#endif
	n = recv(port->sock, ptr, len, 0);
#ifdef WIN32
	pgwin32_noblock = false;
#endif

	return n;
}