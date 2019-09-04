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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  ef (char*,int,char const*) ; 

__attribute__((used)) static void exi_dir1 (RAnalOp *op, ut8 addr, const char *operation) {
	if (addr < 0x80) {
		ef ("_idata,%d,+,%s=[1],", addr, operation);
	} else {
		ef ("_sfr,%d,+,%s=[1],", addr, operation);
	}
}