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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  prio ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PRIORITY ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static unsigned int get_priority(int sd)
{
	unsigned int prio = 0;
	socklen_t optlen = sizeof(prio);
	int rc;

	rc = getsockopt(sd, SOL_SOCKET, SO_PRIORITY, &prio, &optlen);
	if (rc < 0)
		perror("getsockopt(SO_PRIORITY)");

	return prio;
}