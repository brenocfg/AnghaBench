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
typedef  unsigned int u32 ;
struct ath_softc {unsigned int mem; } ;

/* Variables and functions */
 unsigned int ioread32 (unsigned int) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int __ath9k_reg_rmw(struct ath_softc *sc, u32 reg_offset,
				    u32 set, u32 clr)
{
	u32 val;

	val = ioread32(sc->mem + reg_offset);
	val &= ~clr;
	val |= set;
	iowrite32(val, sc->mem + reg_offset);

	return val;
}