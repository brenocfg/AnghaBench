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

/* Variables and functions */
 int mppe_init (void*,unsigned char*,int,int,int,char*) ; 

__attribute__((used)) static int
mppe_decomp_init(void *arg, unsigned char *options, int optlen, int unit,
		 int hdrlen, int mru, int debug)
{
	/* ARGSUSED */
	return mppe_init(arg, options, optlen, unit, debug, "mppe_decomp_init");
}