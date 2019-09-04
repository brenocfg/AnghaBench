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
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ area; } ;
struct TYPE_4__ {TYPE_1__ silent_page; } ;
struct snd_trident {TYPE_2__ tlb; } ;

/* Variables and functions */
 int UNIT_PAGES ; 
 int /*<<< orphan*/  __set_tlb_bus (struct snd_trident*,int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_silent_tlb(struct snd_trident *trident, int page)
{
	int i;
	page *= UNIT_PAGES;
	for (i = 0; i < UNIT_PAGES; i++, page++)
		__set_tlb_bus(trident, page, (unsigned long)trident->tlb.silent_page.area, trident->tlb.silent_page.addr);
}