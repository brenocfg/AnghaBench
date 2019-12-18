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
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  TranslateSocketError () ; 
 int listen (int /*<<< orphan*/ ,int) ; 

int
pgwin32_listen(SOCKET s, int backlog)
{
	int			res;

	res = listen(s, backlog);
	if (res < 0)
		TranslateSocketError();
	return res;
}