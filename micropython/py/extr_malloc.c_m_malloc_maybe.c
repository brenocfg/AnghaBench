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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_printf (char*,size_t,void*) ; 
 size_t MP_STATE_MEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_PEAK () ; 
 int /*<<< orphan*/  current_bytes_allocated ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  total_bytes_allocated ; 

void *m_malloc_maybe(size_t num_bytes) {
    void *ptr = malloc(num_bytes);
#if MICROPY_MEM_STATS
    MP_STATE_MEM(total_bytes_allocated) += num_bytes;
    MP_STATE_MEM(current_bytes_allocated) += num_bytes;
    UPDATE_PEAK();
#endif
    DEBUG_printf("malloc %d : %p\n", num_bytes, ptr);
    return ptr;
}