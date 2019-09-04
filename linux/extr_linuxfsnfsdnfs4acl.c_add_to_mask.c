#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  allow; } ;
struct posix_acl_state {TYPE_1__ mask; } ;
struct posix_ace_state {int /*<<< orphan*/  allow; } ;

/* Variables and functions */

__attribute__((used)) static inline void add_to_mask(struct posix_acl_state *state, struct posix_ace_state *astate)
{
	state->mask.allow |= astate->allow;
}