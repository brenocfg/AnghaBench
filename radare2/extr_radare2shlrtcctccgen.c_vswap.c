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
typedef  int /*<<< orphan*/  SValue ;

/* Variables and functions */
 int /*<<< orphan*/ * vtop ; 

void vswap(void) {
	SValue tmp;
	/* cannot let cpu flags if other instruction are generated. Also
	   avoid leaving VT_JMP anywhere except on the top of the stack
	   because it would complicate the code generator. */
	tmp = vtop[0];
	vtop[0] = vtop[-1];
	vtop[-1] = tmp;

/* XXX: +2% overall speed possible with optimized memswap
 *
 *  memswap(&vtop[0], &vtop[1], sizeof *vtop);
 */
}