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
struct batadv_bla_claim {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int jhash (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline u32 batadv_choose_backbone_gw(const void *data, u32 size)
{
	const struct batadv_bla_claim *claim = (struct batadv_bla_claim *)data;
	u32 hash = 0;

	hash = jhash(&claim->addr, sizeof(claim->addr), hash);
	hash = jhash(&claim->vid, sizeof(claim->vid), hash);

	return hash % size;
}