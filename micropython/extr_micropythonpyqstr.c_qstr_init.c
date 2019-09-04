#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  qstr_pool_t ;
typedef  int /*<<< orphan*/ * MP_STATE_VM ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_POOL ; 

void qstr_init(void) {
    MP_STATE_VM(last_pool) = (qstr_pool_t*)&CONST_POOL; // we won't modify the const_pool since it has no allocated room left
    MP_STATE_VM(qstr_last_chunk) = NULL;

    #if MICROPY_PY_THREAD
    mp_thread_mutex_init(&MP_STATE_VM(qstr_mutex));
    #endif
}