#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct minstrel_ht_sta {TYPE_2__* groups; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct TYPE_3__ {int prob_ewma; } ;

/* Variables and functions */
 int MCS_GROUP_RATES ; 

__attribute__((used)) static inline int
minstrel_ht_get_prob_ewma(struct minstrel_ht_sta *mi, int rate)
{
	int group = rate / MCS_GROUP_RATES;
	rate %= MCS_GROUP_RATES;
	return mi->groups[group].rates[rate].prob_ewma;
}