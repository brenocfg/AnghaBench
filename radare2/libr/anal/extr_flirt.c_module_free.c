#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* free; } ;
struct TYPE_5__ {TYPE_2__* referenced_functions; TYPE_2__* tail_bytes; TYPE_2__* public_functions; } ;
typedef  void* RListFree ;
typedef  TYPE_1__ RFlirtModule ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (TYPE_2__*) ; 

__attribute__((used)) static void module_free(RFlirtModule *module) {
	if (!module) {
		return;
	}
	if (module->public_functions) {
		module->public_functions->free = (RListFree) free;
		r_list_free (module->public_functions);
	}
	if (module->tail_bytes) {
		module->tail_bytes->free = (RListFree) free;
		r_list_free (module->tail_bytes);
	}
	if (module->referenced_functions) {
		module->referenced_functions->free = (RListFree) free;
		r_list_free (module->referenced_functions);
	}
	free (module);
}