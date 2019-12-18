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
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 void* realloc (void*,size_t) ; 
 int umull_overflow (size_t,size_t,size_t*) ; 

void *reallocarray(void *optr, size_t nmemb, size_t size)
{
    size_t total_size;
    if (UNLIKELY(umull_overflow(nmemb, size, &total_size))) {
        errno = ENOMEM;
        return NULL;
    }
    if (UNLIKELY(total_size == 0)) {
        free(optr);
        return malloc(1);
    }
    return realloc(optr, total_size);
}