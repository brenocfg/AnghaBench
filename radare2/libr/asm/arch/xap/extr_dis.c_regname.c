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
#define  REG_AH 131 
#define  REG_AL 130 
#define  REG_X 129 
#define  REG_Y 128 

__attribute__((used)) static char *regname(int reg) {
	switch (reg) {
	case REG_AH: return "AH";
	case REG_AL: return "AL";
	case REG_X: return "X";
	case REG_Y: return "Y";
	}
	return NULL;
}