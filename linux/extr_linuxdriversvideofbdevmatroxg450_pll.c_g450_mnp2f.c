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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g450_mnp2vco (struct matrox_fb_info const*,unsigned int) ; 
 unsigned int g450_vco2f (unsigned int,int /*<<< orphan*/ ) ; 

unsigned int g450_mnp2f(const struct matrox_fb_info *minfo, unsigned int mnp)
{
	return g450_vco2f(mnp, g450_mnp2vco(minfo, mnp));
}