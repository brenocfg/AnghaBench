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
struct aa_dfa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_MATCH_WB (int /*<<< orphan*/ ) ; 
 unsigned int leftmatch_fb (struct aa_dfa*,unsigned int,char const*,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  wb ; 

unsigned int aa_dfa_leftmatch(struct aa_dfa *dfa, unsigned int start,
			      const char *str, unsigned int *count)
{
	DEFINE_MATCH_WB(wb);

	/* TODO: match for extended state dfas */

	return leftmatch_fb(dfa, start, str, &wb, count);
}