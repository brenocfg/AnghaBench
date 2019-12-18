#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* init ) () ;int /*<<< orphan*/  (* deinit ) () ;} ;
typedef  TYPE_1__ io_backend_t ;

/* Variables and functions */
 TYPE_1__** io_backends ; 
 TYPE_1__* sel_backend ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

int iob_select(const char *name) {
	io_backend_t *iob;

	iob = io_backends[0];

	if (!iob) {
		return 0;
	}

	if (sel_backend && sel_backend->deinit) {
		sel_backend->deinit ();
	}

	sel_backend = iob;

	if (sel_backend->init) {
		sel_backend->init ();
	}

	return 1;
}