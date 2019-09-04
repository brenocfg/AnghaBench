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
struct calldata {int /*<<< orphan*/  stack; int /*<<< orphan*/  fixed; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void calldata_free(struct calldata *data)
{
	if (!data->fixed)
		bfree(data->stack);
}