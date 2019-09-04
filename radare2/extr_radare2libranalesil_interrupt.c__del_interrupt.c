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
typedef  scalar_t__ ut32 ;
struct TYPE_3__ {int /*<<< orphan*/ * intr0; int /*<<< orphan*/  interrupts; } ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  dict_del (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _del_interrupt(RAnalEsil *esil, ut32 intr_num) {
	if (intr_num) {
		dict_del (esil->interrupts, intr_num);
	} else {
		esil->intr0 = NULL;
	}
}