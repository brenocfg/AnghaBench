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
struct cfb_info {int dummy; } ;

/* Variables and functions */
 unsigned int cyber2000fb_readb (int,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_writeb (unsigned int,int,struct cfb_info*) ; 

__attribute__((used)) static inline unsigned int
cyber2000_grphr(unsigned int reg, struct cfb_info *cfb)
{
	cyber2000fb_writeb(reg, 0x3ce, cfb);
	return cyber2000fb_readb(0x3cf, cfb);
}