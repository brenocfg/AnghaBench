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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  drxt ;

/* Variables and functions */
 size_t DR_CONTROL ; 
#define  DR_LEN_1 131 
#define  DR_LEN_2 130 
#define  DR_LEN_4 129 
#define  DR_LEN_8 128 
 int I386_DR_GET_RW_LEN (int /*<<< orphan*/ ,int) ; 
 int I386_DR_IS_ENABLED (int /*<<< orphan*/ ,int) ; 
 int I386_DR_IS_LOCAL_ENABLED (int /*<<< orphan*/ ,int) ; 

ut64 drx_get(drxt *drx, int n, int *rwx, int *len, int *global, int *enabled) {
	int ret = I386_DR_GET_RW_LEN (drx[DR_CONTROL], n);
	if (global) {
		*global = I386_DR_IS_LOCAL_ENABLED (drx[7], n);
	}
	if (len) {
		switch (ret & 0xA) {
		case DR_LEN_1: *len = 1; break;
		case DR_LEN_2: *len = 2; break;
		case DR_LEN_4: *len = 4; break;
		case DR_LEN_8: *len = 8; break;
		default: *len = 0; break;
		}
	}
	if (enabled) {
		*enabled = I386_DR_IS_ENABLED (drx[7], n);
	}
	if (rwx) {
		*rwx = ret & 0x3;
	}
	return (ut64) drx[n];
}