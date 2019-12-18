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
 void* malloc (size_t) ; 

__attribute__((used)) static inline void *lfs1_malloc(size_t size) {
#ifndef LFS1_NO_MALLOC
    return malloc(size);
#else
    (void)size;
    return NULL;
#endif
}