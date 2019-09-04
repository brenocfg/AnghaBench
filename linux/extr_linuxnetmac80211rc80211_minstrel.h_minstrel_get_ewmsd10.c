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
struct minstrel_rate_stats {unsigned int prob_ewmv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINSTREL_TRUNC (unsigned int) ; 
 int int_sqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
minstrel_get_ewmsd10(struct minstrel_rate_stats *mrs)
{
	unsigned int ewmv = mrs->prob_ewmv;
	return int_sqrt(MINSTREL_TRUNC(ewmv * 1000 * 1000));
}