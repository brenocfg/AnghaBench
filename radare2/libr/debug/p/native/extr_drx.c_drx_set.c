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
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  drxt ;

/* Variables and functions */
 size_t DR_CONTROL ; 
 int DR_NADDR ; 
 int /*<<< orphan*/  I386_DR_CONTROL_MASK ; 
 int /*<<< orphan*/  I386_DR_DISABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I386_DR_GLOBAL_ENABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I386_DR_LOCAL_ENABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I386_DR_SET_RW_LEN (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 

int drx_set(drxt *drx, int n, ut64 addr, int len, int rwx, int global) {
	ut32 control = drx[DR_CONTROL];
	if (n < 0 || n >= DR_NADDR) {
		eprintf ("Invalid DRX index (0-%d)\n", DR_NADDR - 1);
		return false;
	}
	switch (rwx) {
	case 1: rwx = 0; break;
	case 2: rwx = 1; break;
	case 4: rwx = 3; break;
	default:
		rwx = 0;
	}
	switch (len) {
	case 1: len = 0; break;
	case 2: len = 1 << 2; break;
	case 4: len = 3 << 2; break;
	case 8: len = 2 << 2; break;	// AMD64 only
	case -1:
	{
		I386_DR_DISABLE (control, n);
		control &= I386_DR_CONTROL_MASK;
		drx[DR_CONTROL] = control;
		drx[n] = 0;
		return true;
	}
	default:
		eprintf ("Invalid DRX length (%d) must be 1, 2, 4, 8 bytes\n", len);
		return false;
	}
	I386_DR_SET_RW_LEN (control, n, len | rwx);
	if (global) {
		I386_DR_GLOBAL_ENABLE (control, n);
		// control |= DR_GLOBAL_SLOWDOWN;
	} else {
		I386_DR_LOCAL_ENABLE (control, n);
		// control |= DR_LOCAL_SLOWDOWN; // XXX: This is wrong
	}
	control &= I386_DR_CONTROL_MASK;
	drx[n] = addr;
// eprintf ("drx[DR_CONTROL] = %x \n", drx[DR_CONTROL]);
	drx[DR_CONTROL] = control;
// eprintf ("CONTROL = %x\n", control);
	return true;
}