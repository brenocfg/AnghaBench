#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
#define  R_ANAL_ARCHINFO_ALIGN 130 
#define  R_ANAL_ARCHINFO_MAX_OP_SIZE 129 
#define  R_ANAL_ARCHINFO_MIN_OP_SIZE 128 

__attribute__((used)) static int archinfo(RAnal *anal, int query) {
	if (anal->bits != 16) {
		return -1;
	}
	switch (query) {
	case R_ANAL_ARCHINFO_ALIGN:
		return 2;
	case R_ANAL_ARCHINFO_MIN_OP_SIZE:
		/* all ops are at least 1 word long */
		return 2;
	case R_ANAL_ARCHINFO_MAX_OP_SIZE:
		return 8;
	default:
		return -1;
	}
}