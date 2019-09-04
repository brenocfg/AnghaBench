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
typedef  scalar_t__ u16 ;
struct tridentfb_par {scalar_t__ io_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_readb (scalar_t__) ; 

__attribute__((used)) static inline u8 t_inb(struct tridentfb_par *p, u16 reg)
{
	return fb_readb(p->io_virt + reg);
}