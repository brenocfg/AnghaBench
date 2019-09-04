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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sockopt ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_FANOUT ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void sock_fanout_getopts(int fd, uint16_t *typeflags, uint16_t *group_id)
{
	int sockopt;
	socklen_t sockopt_len = sizeof(sockopt);

	if (getsockopt(fd, SOL_PACKET, PACKET_FANOUT,
		       &sockopt, &sockopt_len)) {
		perror("failed to getsockopt");
		exit(1);
	}
	*typeflags = sockopt >> 16;
	*group_id = sockopt & 0xfffff;
}