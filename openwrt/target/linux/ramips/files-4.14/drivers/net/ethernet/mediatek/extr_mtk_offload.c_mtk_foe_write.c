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
typedef  size_t u32 ;
struct mtk_foe_entry {int dummy; } ;
struct mtk_eth {scalar_t__ foe_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct mtk_foe_entry*,struct mtk_foe_entry*,int) ; 

__attribute__((used)) static void
mtk_foe_write(struct mtk_eth *eth, u32 hash,
	      struct mtk_foe_entry *entry)
{
	struct mtk_foe_entry *table = (struct mtk_foe_entry *)eth->foe_table;

	memcpy(&table[hash], entry, sizeof(*entry));
}