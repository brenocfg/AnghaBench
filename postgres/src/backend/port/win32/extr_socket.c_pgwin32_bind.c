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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  TranslateSocketError () ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 

int
pgwin32_bind(SOCKET s, struct sockaddr *addr, int addrlen)
{
	int			res;

	res = bind(s, addr, addrlen);
	if (res < 0)
		TranslateSocketError();
	return res;
}