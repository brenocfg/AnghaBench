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
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */

__attribute__((used)) static int esil_x86_cs_init(RAnalEsil *esil) {
	if (!esil) {
		return false;
	}
	// XXX. this depends on kernel
	// r_anal_esil_set_interrupt (esil, 0x80, x86_int_0x80);
	/* disable by default */
//	r_anal_esil_set_interrupt (esil, 0x80, NULL);	// this is stupid, don't do this
	return true;
}