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
typedef  int /*<<< orphan*/  u8 ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALCON_STAT_COUNT ; 
 size_t ef4_nic_describe_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  falcon_stat_desc ; 
 int /*<<< orphan*/  falcon_stat_mask ; 

__attribute__((used)) static size_t falcon_describe_nic_stats(struct ef4_nic *efx, u8 *names)
{
	return ef4_nic_describe_stats(falcon_stat_desc, FALCON_STAT_COUNT,
				      falcon_stat_mask, names);
}