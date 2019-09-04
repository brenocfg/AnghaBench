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
 unsigned long CFG_SZ_16 ; 
 unsigned long CFG_SZ_18 ; 
 unsigned long CFG_SZ_20 ; 
 unsigned long CFG_SZ_24 ; 
 unsigned long CFG_SZ_8 ; 

__attribute__((used)) static unsigned long msbits_to_reg(int msbits)
{
	switch (msbits) {
	case 8:
		return CFG_SZ_8;
	case 16:
		return CFG_SZ_16;
	case 18:
		return CFG_SZ_18;
	case 20:
		return CFG_SZ_20;
	case 24:
		return CFG_SZ_24;
	}
	return 0;
}