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
struct lfs2_ctz {void* size; void* head; } ;

/* Variables and functions */
 void* lfs2_fromle32 (void*) ; 

__attribute__((used)) static void lfs2_ctz_fromle32(struct lfs2_ctz *ctz) {
    ctz->head = lfs2_fromle32(ctz->head);
    ctz->size = lfs2_fromle32(ctz->size);
}