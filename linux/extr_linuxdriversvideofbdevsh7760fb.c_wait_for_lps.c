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
struct sh7760fb_par {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ LDPMMR ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int wait_for_lps(struct sh7760fb_par *par, int val)
{
	int i = 100;
	while (--i && ((ioread16(par->base + LDPMMR) & 3) != val))
		msleep(1);

	if (i <= 0)
		return -ETIMEDOUT;

	return 0;
}