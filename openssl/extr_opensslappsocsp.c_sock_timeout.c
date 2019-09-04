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
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SHUT_RD ; 
 int acfd ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sock_timeout(int signum)
{
    if (acfd != (int)INVALID_SOCKET)
        (void)shutdown(acfd, SHUT_RD);
}