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
struct subchannel {int dummy; } ;
struct chp_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __s390_subchannel_vary_chpid (struct subchannel*,struct chp_id,int) ; 

__attribute__((used)) static int s390_subchannel_vary_chpid_on(struct subchannel *sch, void *data)
{
	struct chp_id *chpid = data;

	__s390_subchannel_vary_chpid(sch, *chpid, 1);
	return 0;
}