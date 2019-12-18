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
struct bplus_header {int flags; } ;

/* Variables and functions */
 int BP_internal ; 

__attribute__((used)) static inline bool bp_internal(struct bplus_header *bp)
{
	return bp->flags & BP_internal;
}