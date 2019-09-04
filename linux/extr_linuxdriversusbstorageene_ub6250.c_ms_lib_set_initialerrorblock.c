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
typedef  int /*<<< orphan*/  u16 ;
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_LB_INITIAL_ERROR ; 
 int ms_lib_set_logicalblockmark (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_lib_set_initialerrorblock(struct us_data *us, u16 phyblk)
{
	return ms_lib_set_logicalblockmark(us, phyblk, MS_LB_INITIAL_ERROR);
}