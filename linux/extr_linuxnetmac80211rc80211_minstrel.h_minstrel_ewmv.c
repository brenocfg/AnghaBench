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
 int MINSTREL_TRUNC (int) ; 

__attribute__((used)) static inline int
minstrel_ewmv(int old_ewmv, int cur_prob, int prob_ewma, int weight)
{
	int diff, incr;

	diff = cur_prob - prob_ewma;
	incr = (EWMA_DIV - weight) * diff / EWMA_DIV;
	return weight * (old_ewmv + MINSTREL_TRUNC(diff * incr)) / EWMA_DIV;
}