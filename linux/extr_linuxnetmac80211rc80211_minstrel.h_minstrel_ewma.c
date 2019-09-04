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
 int EWMA_DIV ; 

__attribute__((used)) static inline int
minstrel_ewma(int old, int new, int weight)
{
	int diff, incr;

	diff = new - old;
	incr = (EWMA_DIV - weight) * diff / EWMA_DIV;

	return old + incr;
}