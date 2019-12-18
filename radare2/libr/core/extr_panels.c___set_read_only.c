#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* model; } ;
struct TYPE_4__ {char* readOnly; } ;
typedef  TYPE_2__ RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 

void __set_read_only(RPanel *p, char *s) {
	free (p->model->readOnly);
	p->model->readOnly = s;
}