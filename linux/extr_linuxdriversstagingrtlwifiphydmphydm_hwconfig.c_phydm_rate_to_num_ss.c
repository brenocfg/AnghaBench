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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ ODM_RATE54M ; 
 scalar_t__ ODM_RATEMCS0 ; 
 scalar_t__ ODM_RATEMCS31 ; 
 scalar_t__ ODM_RATEVHTSS1MCS9 ; 
 scalar_t__ ODM_RATEVHTSS2MCS9 ; 
 scalar_t__ ODM_RATEVHTSS3MCS9 ; 
 scalar_t__ ODM_RATEVHTSS4MCS9 ; 

__attribute__((used)) static u8 phydm_rate_to_num_ss(struct phy_dm_struct *dm, u8 data_rate)
{
	u8 num_ss = 1;

	if (data_rate <= ODM_RATE54M)
		num_ss = 1;
	else if (data_rate <= ODM_RATEMCS31)
		num_ss = ((data_rate - ODM_RATEMCS0) >> 3) + 1;
	else if (data_rate <= ODM_RATEVHTSS1MCS9)
		num_ss = 1;
	else if (data_rate <= ODM_RATEVHTSS2MCS9)
		num_ss = 2;
	else if (data_rate <= ODM_RATEVHTSS3MCS9)
		num_ss = 3;
	else if (data_rate <= ODM_RATEVHTSS4MCS9)
		num_ss = 4;

	return num_ss;
}