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
typedef  int /*<<< orphan*/  tss ;
struct scm_timestamping_internal {int /*<<< orphan*/ * ts; } ;
struct scm_timestamping {int /*<<< orphan*/ * ts; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TIMESTAMPING_OLD ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scm_timestamping*) ; 
 int /*<<< orphan*/  timespec64_to_timespec (int /*<<< orphan*/ ) ; 

void put_cmsg_scm_timestamping(struct msghdr *msg, struct scm_timestamping_internal *tss_internal)
{
	struct scm_timestamping tss;
	int i;

	for (i = 0; i < ARRAY_SIZE(tss.ts); i++)
		tss.ts[i] = timespec64_to_timespec(tss_internal->ts[i]);

	put_cmsg(msg, SOL_SOCKET, SO_TIMESTAMPING_OLD, sizeof(tss), &tss);
}