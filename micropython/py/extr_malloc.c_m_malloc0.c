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
 void* m_malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *m_malloc0(size_t num_bytes) {
    void *ptr = m_malloc(num_bytes);
    // If this config is set then the GC clears all memory, so we don't need to.
    #if !MICROPY_GC_CONSERVATIVE_CLEAR
    memset(ptr, 0, num_bytes);
    #endif
    return ptr;
}