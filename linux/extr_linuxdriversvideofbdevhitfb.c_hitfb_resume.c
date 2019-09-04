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
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HD64461_STBCR ; 
 int /*<<< orphan*/  HD64461_STBCR_SLCKE_IST ; 
 int /*<<< orphan*/  HD64461_STBCR_SLCKE_OST ; 
 int /*<<< orphan*/  fb_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hitfb_blank (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hitfb_resume(struct device *dev)
{
	u16 v;

	v = fb_readw(HD64461_STBCR);
	v &= ~HD64461_STBCR_SLCKE_OST;
	msleep(100);
	v = fb_readw(HD64461_STBCR);
	v &= ~HD64461_STBCR_SLCKE_IST;
	fb_writew(v, HD64461_STBCR);
	hitfb_blank(0,0);

	return 0;
}