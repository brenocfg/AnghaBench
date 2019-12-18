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
struct lfs2_gstate {void** pair; void* tag; } ;

/* Variables and functions */
 void* lfs2_tole32 (void*) ; 

__attribute__((used)) static inline void lfs2_gstate_tole32(struct lfs2_gstate *a) {
    a->tag     = lfs2_tole32(a->tag);
    a->pair[0] = lfs2_tole32(a->pair[0]);
    a->pair[1] = lfs2_tole32(a->pair[1]);
}