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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  reason; } ;
typedef  TYPE_1__ MYSQLI_WARNING ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

void php_clear_warnings(MYSQLI_WARNING *w)
{
	MYSQLI_WARNING *n;

	while (w) {
		n = w;
		zval_ptr_dtor_str(&(w->reason));
		zval_ptr_dtor_str(&(w->sqlstate));
		w = w->next;
		efree(n);
	}
}