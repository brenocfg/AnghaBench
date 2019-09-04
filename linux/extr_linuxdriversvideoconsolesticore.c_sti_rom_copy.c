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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  gsc_readb (unsigned long) ; 
 int /*<<< orphan*/  gsc_readl (unsigned long) ; 
 int /*<<< orphan*/  sti_flush (unsigned long,unsigned long) ; 

__attribute__((used)) static void sti_rom_copy(unsigned long base, unsigned long count, void *dest)
{
	unsigned long dest_start = (unsigned long) dest;

	/* this still needs to be revisited (see arch/parisc/mm/init.c:246) ! */
	while (count >= 4) {
		count -= 4;
		*(u32 *)dest = gsc_readl(base);
		base += 4;
		dest += 4;
	}
	while (count) {
		count--;
		*(u8 *)dest = gsc_readb(base);
		base++;
		dest++;
	}

	sti_flush(dest_start, (unsigned long)dest);
}