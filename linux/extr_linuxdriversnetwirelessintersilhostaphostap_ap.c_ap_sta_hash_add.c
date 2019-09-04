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
struct sta_info {int /*<<< orphan*/  addr; struct sta_info* hnext; } ;
struct ap_data {struct sta_info** sta_hash; } ;

/* Variables and functions */
 size_t STA_HASH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_sta_hash_add(struct ap_data *ap, struct sta_info *sta)
{
	sta->hnext = ap->sta_hash[STA_HASH(sta->addr)];
	ap->sta_hash[STA_HASH(sta->addr)] = sta;
}