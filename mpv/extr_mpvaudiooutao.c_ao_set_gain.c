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
struct ao {int /*<<< orphan*/  gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,float) ; 

void ao_set_gain(struct ao *ao, float gain)
{
    atomic_store(&ao->gain, gain);
}