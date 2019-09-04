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
 scalar_t__ WARN_ON (int) ; 
 unsigned int aio_nr ; 
 int /*<<< orphan*/  aio_nr_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aio_nr_sub(unsigned nr)
{
	spin_lock(&aio_nr_lock);
	if (WARN_ON(aio_nr - nr > aio_nr))
		aio_nr = 0;
	else
		aio_nr -= nr;
	spin_unlock(&aio_nr_lock);
}