#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * err_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 TYPE_1__ global ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cxlflash_free_errpage(void)
{

	mutex_lock(&global.mutex);
	if (global.err_page) {
		__free_page(global.err_page);
		global.err_page = NULL;
	}
	mutex_unlock(&global.mutex);
}