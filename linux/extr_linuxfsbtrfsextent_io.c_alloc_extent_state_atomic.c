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
struct extent_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct extent_state* alloc_extent_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct extent_state *
alloc_extent_state_atomic(struct extent_state *prealloc)
{
	if (!prealloc)
		prealloc = alloc_extent_state(GFP_ATOMIC);

	return prealloc;
}