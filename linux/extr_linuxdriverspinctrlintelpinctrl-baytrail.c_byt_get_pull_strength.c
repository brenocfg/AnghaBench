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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  BYT_PULL_STR_10K 131 
#define  BYT_PULL_STR_20K 130 
#define  BYT_PULL_STR_2K 129 
#define  BYT_PULL_STR_40K 128 
 int BYT_PULL_STR_MASK ; 

__attribute__((used)) static void byt_get_pull_strength(u32 reg, u16 *strength)
{
	switch (reg & BYT_PULL_STR_MASK) {
	case BYT_PULL_STR_2K:
		*strength = 2000;
		break;
	case BYT_PULL_STR_10K:
		*strength = 10000;
		break;
	case BYT_PULL_STR_20K:
		*strength = 20000;
		break;
	case BYT_PULL_STR_40K:
		*strength = 40000;
		break;
	}
}