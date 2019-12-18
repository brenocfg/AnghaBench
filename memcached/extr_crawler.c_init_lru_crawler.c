#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * c; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * mod; TYPE_1__ c; } ;

/* Variables and functions */
 TYPE_2__ active_crawler_mod ; 
 int lru_crawler_initialized ; 
 void* storage ; 

int init_lru_crawler(void *arg) {
    if (lru_crawler_initialized == 0) {
#ifdef EXTSTORE
        storage = arg;
#endif
        active_crawler_mod.c.c = NULL;
        active_crawler_mod.mod = NULL;
        active_crawler_mod.data = NULL;
        lru_crawler_initialized = 1;
    }
    return 0;
}