#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cap; } ;
struct cw1200_ht_info {int operation_mode; TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int IEEE80211_HT_CAP_GRN_FLD ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 scalar_t__ cw1200_is_ht (struct cw1200_ht_info const*) ; 

__attribute__((used)) static inline int cw1200_ht_greenfield(const struct cw1200_ht_info *ht_info)
{
	return cw1200_is_ht(ht_info) &&
		(ht_info->ht_cap.cap & IEEE80211_HT_CAP_GRN_FLD) &&
		!(ht_info->operation_mode &
		  IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
}