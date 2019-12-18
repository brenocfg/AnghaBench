#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ map; } ;
typedef  TYPE_1__ tms320_dasm_t ;
struct TYPE_8__ {int /*<<< orphan*/  byte; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  TMS320_F_CPU_C55X ; 
 TYPE_4__* c55x_list ; 
 int /*<<< orphan*/  ht_up_insert (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ht_up_new0 () ; 
 int /*<<< orphan*/  tms320_f_set_cpu (TYPE_1__*,int /*<<< orphan*/ ) ; 

int tms320_dasm_init(tms320_dasm_t * dasm) {
	int i = 0;

	if (dasm->map) {
		/* already initialized */
		return 0;
	}

	dasm->map = ht_up_new0 ();
	if (!dasm->map) {
		return 0;
	}
	for (i = 0; i < ARRAY_SIZE(c55x_list); i++) {
		ht_up_insert (dasm->map, c55x_list[i].byte, &c55x_list[i]);
	}

	tms320_f_set_cpu(dasm, TMS320_F_CPU_C55X);

	return 0;
}