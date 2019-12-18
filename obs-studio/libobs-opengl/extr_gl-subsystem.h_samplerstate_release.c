#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ gs_samplerstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void samplerstate_release(gs_samplerstate_t *ss)
{
	if (os_atomic_dec_long(&ss->ref) == 0)
		bfree(ss);
}