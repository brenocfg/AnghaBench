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
 scalar_t__ calloc (int,int) ; 
 void** r_flist_init (void**,int) ; 

__attribute__((used)) static inline void **r_flist_new(int n) {
	void **it;
	if (((n + 2) * sizeof(void*)) < sizeof(void*)) return NULL;
	if (!(it = (void **)calloc ((n + 2), sizeof (void*)))) {
		return NULL;
	}
	return r_flist_init (it, n);
}