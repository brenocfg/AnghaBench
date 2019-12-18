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
 scalar_t__ Geqo_generations ; 

__attribute__((used)) static int
gimme_number_generations(int pool_size)
{
	if (Geqo_generations > 0)
		return Geqo_generations;

	return pool_size;
}