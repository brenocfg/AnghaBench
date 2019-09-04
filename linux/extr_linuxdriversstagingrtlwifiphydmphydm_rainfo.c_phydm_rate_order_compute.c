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

/* Variables and functions */
 scalar_t__ ODM_RATEMCS16 ; 
 scalar_t__ ODM_RATEMCS24 ; 
 scalar_t__ ODM_RATEMCS8 ; 
 scalar_t__ ODM_RATEVHTSS1MCS0 ; 
 scalar_t__ ODM_RATEVHTSS2MCS0 ; 
 scalar_t__ ODM_RATEVHTSS3MCS0 ; 
 scalar_t__ ODM_RATEVHTSS4MCS0 ; 

u8 phydm_rate_order_compute(void *dm_void, u8 rate_idx)
{
	u8 rate_order = 0;

	if (rate_idx >= ODM_RATEVHTSS4MCS0) {
		rate_idx -= ODM_RATEVHTSS4MCS0;
		/**/
	} else if (rate_idx >= ODM_RATEVHTSS3MCS0) {
		rate_idx -= ODM_RATEVHTSS3MCS0;
		/**/
	} else if (rate_idx >= ODM_RATEVHTSS2MCS0) {
		rate_idx -= ODM_RATEVHTSS2MCS0;
		/**/
	} else if (rate_idx >= ODM_RATEVHTSS1MCS0) {
		rate_idx -= ODM_RATEVHTSS1MCS0;
		/**/
	} else if (rate_idx >= ODM_RATEMCS24) {
		rate_idx -= ODM_RATEMCS24;
		/**/
	} else if (rate_idx >= ODM_RATEMCS16) {
		rate_idx -= ODM_RATEMCS16;
		/**/
	} else if (rate_idx >= ODM_RATEMCS8) {
		rate_idx -= ODM_RATEMCS8;
		/**/
	}
	rate_order = rate_idx;

	return rate_order;
}