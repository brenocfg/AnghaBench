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
typedef  int /*<<< orphan*/  RAnalEsilInterrupt ;
typedef  TYPE_1__ RAnalEsil ;

/* Variables and functions */
 scalar_t__ dict_getu (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static RAnalEsilInterrupt *_get_interrupt(RAnalEsil *esil, ut32 intr_num) {
	return intr_num ?
		(RAnalEsilInterrupt *)dict_getu(esil->interrupts, intr_num) :
		esil->intr0;
}