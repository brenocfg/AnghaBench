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
typedef  int /*<<< orphan*/  mark ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_MARK ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static unsigned int get_somark(int sd)
{
	unsigned int mark = 0;
	socklen_t optlen = sizeof(mark);
	int rc;

	rc = getsockopt(sd, SOL_SOCKET, SO_MARK, &mark, &optlen);
	if (rc < 0)
		perror("getsockopt(SO_MARK)");

	return mark;
}