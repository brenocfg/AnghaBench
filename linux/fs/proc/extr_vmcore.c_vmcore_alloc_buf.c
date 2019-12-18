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
 char* vmalloc_user (size_t) ; 
 char* vzalloc (size_t) ; 

__attribute__((used)) static inline char *vmcore_alloc_buf(size_t size)
{
#ifdef CONFIG_MMU
	return vmalloc_user(size);
#else
	return vzalloc(size);
#endif
}