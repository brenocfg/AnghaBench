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
struct mld2_query {int dummy; } ;
struct inet6_dev {unsigned long mc_maxdelay; } ;

/* Variables and functions */
 unsigned long max (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mld_update_qi (struct inet6_dev*,struct mld2_query*) ; 
 int /*<<< orphan*/  mld_update_qri (struct inet6_dev*,struct mld2_query*) ; 
 int /*<<< orphan*/  mld_update_qrv (struct inet6_dev*,struct mld2_query*) ; 
 int /*<<< orphan*/  mldv2_mrc (struct mld2_query*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mld_process_v2(struct inet6_dev *idev, struct mld2_query *mld,
			  unsigned long *max_delay)
{
	*max_delay = max(msecs_to_jiffies(mldv2_mrc(mld)), 1UL);

	mld_update_qrv(idev, mld);
	mld_update_qi(idev, mld);
	mld_update_qri(idev, mld);

	idev->mc_maxdelay = *max_delay;

	return 0;
}