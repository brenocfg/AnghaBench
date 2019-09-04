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
struct zoran {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR36057_POR ; 
 unsigned int ZR36057_POR_POTime ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ post_office_wait (struct zoran*) ; 

int
post_office_read (struct zoran *zr,
		  unsigned int  guest,
		  unsigned int  reg)
{
	u32 por;

	por = ZR36057_POR_POTime | ((guest & 7) << 20) | ((reg & 7) << 16);
	btwrite(por, ZR36057_POR);
	if (post_office_wait(zr) < 0) {
		return -1;
	}

	return btread(ZR36057_POR) & 0xFF;
}