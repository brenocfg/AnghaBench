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
struct TYPE_3__ {char** stack; int stackptr; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */

__attribute__((used)) static int esil_swap(RAnalEsil *esil) {
	char *tmp;
	if (!esil || !esil->stack || esil->stackptr < 2) {
		return false;
	}
	if (!esil->stack[esil->stackptr-1] || !esil->stack[esil->stackptr-2]) {
		return false;
	}
	tmp = esil->stack[esil->stackptr-1];
	esil->stack[esil->stackptr-1] = esil->stack[esil->stackptr-2];
	esil->stack[esil->stackptr-2] = tmp;
	return true;
}