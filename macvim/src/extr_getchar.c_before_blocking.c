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
 int /*<<< orphan*/  garbage_collect () ; 
 scalar_t__ may_garbage_collect ; 
 int /*<<< orphan*/  updatescript (int /*<<< orphan*/ ) ; 

void
before_blocking()
{
    updatescript(0);
#ifdef FEAT_EVAL
    if (may_garbage_collect)
	garbage_collect();
#endif
}