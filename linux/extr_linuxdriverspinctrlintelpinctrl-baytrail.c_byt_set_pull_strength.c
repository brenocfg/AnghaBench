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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_PULL_STR_10K ; 
 int /*<<< orphan*/  BYT_PULL_STR_20K ; 
 int /*<<< orphan*/  BYT_PULL_STR_2K ; 
 int /*<<< orphan*/  BYT_PULL_STR_40K ; 
 int /*<<< orphan*/  BYT_PULL_STR_MASK ; 
 int EINVAL ; 

__attribute__((used)) static int byt_set_pull_strength(u32 *reg, u16 strength)
{
	*reg &= ~BYT_PULL_STR_MASK;

	switch (strength) {
	case 2000:
		*reg |= BYT_PULL_STR_2K;
		break;
	case 10000:
		*reg |= BYT_PULL_STR_10K;
		break;
	case 20000:
		*reg |= BYT_PULL_STR_20K;
		break;
	case 40000:
		*reg |= BYT_PULL_STR_40K;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}