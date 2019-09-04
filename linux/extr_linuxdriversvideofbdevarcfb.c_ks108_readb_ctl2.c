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
struct arcfb_par {int /*<<< orphan*/  c2io_addr; } ;

/* Variables and functions */
 unsigned char inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char ks108_readb_ctl2(struct arcfb_par *par)
{
	return inb(par->c2io_addr);
}