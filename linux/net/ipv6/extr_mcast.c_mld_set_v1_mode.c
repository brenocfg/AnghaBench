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
struct inet6_dev {unsigned long mc_qrv; unsigned long mc_qi; unsigned long mc_qri; scalar_t__ mc_v1_seen; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static void mld_set_v1_mode(struct inet6_dev *idev)
{
	/* RFC3810, relevant sections:
	 *  - 9.1. Robustness Variable
	 *  - 9.2. Query Interval
	 *  - 9.3. Query Response Interval
	 *  - 9.12. Older Version Querier Present Timeout
	 */
	unsigned long switchback;

	switchback = (idev->mc_qrv * idev->mc_qi) + idev->mc_qri;

	idev->mc_v1_seen = jiffies + switchback;
}