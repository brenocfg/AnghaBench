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
struct arcfb_par {unsigned char* cslut; int /*<<< orphan*/  cio_addr; int /*<<< orphan*/  dio_addr; } ;

/* Variables and functions */
 unsigned char KS_CEHI ; 
 unsigned char KS_CELO ; 
 unsigned char KS_SEL_CMD ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuhold ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks108_writeb_ctl(struct arcfb_par *par,
				unsigned int chipindex, unsigned char value)
{
	unsigned char chipselval = par->cslut[chipindex];

	outb(chipselval|KS_CEHI|KS_SEL_CMD, par->cio_addr);
	outb(value, par->dio_addr);
	udelay(tuhold);
	outb(chipselval|KS_CELO|KS_SEL_CMD, par->cio_addr);
}