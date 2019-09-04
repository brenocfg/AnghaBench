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
typedef  int u32 ;
struct batadv_tt_common_entry {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int jhash (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline u32 batadv_choose_tt(const void *data, u32 size)
{
	struct batadv_tt_common_entry *tt;
	u32 hash = 0;

	tt = (struct batadv_tt_common_entry *)data;
	hash = jhash(&tt->addr, ETH_ALEN, hash);
	hash = jhash(&tt->vid, sizeof(tt->vid), hash);

	return hash % size;
}