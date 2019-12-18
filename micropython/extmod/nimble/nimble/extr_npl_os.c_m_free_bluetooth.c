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
typedef  void* MP_STATE_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  m_free (void**) ; 

void m_free_bluetooth(void *ptr_in) {
    void **ptr = &((void**)ptr_in)[-2];
    if (ptr[1] != NULL) {
        ((void**)ptr[1])[0] = ptr[0];
    }
    if (ptr[0] != NULL) {
        ((void**)ptr[0])[1] = ptr[1];
    } else {
        MP_STATE_PORT(bluetooth_nimble_memory) = ptr[1];
    }
    m_free(ptr);
}