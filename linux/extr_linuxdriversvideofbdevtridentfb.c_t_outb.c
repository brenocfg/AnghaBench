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
 int /*<<< orphan*/  fb_writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void t_outb(struct tridentfb_par *p, u8 val, u16 reg)
{
	fb_writeb(val, p->io_virt + reg);
}