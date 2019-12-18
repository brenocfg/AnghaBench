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
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  r_flist_rewind (void**) ; 

__attribute__((used)) static inline void r_flist_delete(void **it, int idx) {
	r_flist_rewind (it);
	free (it[idx]);
	for(it += idx; *it; it++) *it = *(it+1);
}