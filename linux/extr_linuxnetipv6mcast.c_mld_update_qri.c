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
struct inet6_dev {int /*<<< orphan*/  mc_qri; } ;

/* Variables and functions */
 int /*<<< orphan*/  mldv2_mrc (struct mld2_query const*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mld_update_qri(struct inet6_dev *idev,
			   const struct mld2_query *mlh2)
{
	/* RFC3810, relevant sections:
	 *  - 5.1.3. Maximum Response Code
	 *  - 9.3. Query Response Interval
	 */
	idev->mc_qri = msecs_to_jiffies(mldv2_mrc(mlh2));
}