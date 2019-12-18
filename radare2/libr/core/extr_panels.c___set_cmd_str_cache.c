#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* model; } ;
struct TYPE_6__ {char* cmdStrCache; } ;
typedef  TYPE_2__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __set_dcb (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  __set_pcb (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 

void __set_cmd_str_cache(RCore *core, RPanel *p, char *s) {
	free (p->model->cmdStrCache);
	p->model->cmdStrCache = s;
	__set_dcb (core, p);
	__set_pcb (p);
}