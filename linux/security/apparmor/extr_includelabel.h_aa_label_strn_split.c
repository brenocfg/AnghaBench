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
 int /*<<< orphan*/ * ACCEPT_TABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFA_START ; 
 unsigned int aa_dfa_matchn_until (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const**) ; 
 int /*<<< orphan*/  stacksplitdfa ; 

__attribute__((used)) static inline const char *aa_label_strn_split(const char *str, int n)
{
	const char *pos;
	unsigned int state;

	state = aa_dfa_matchn_until(stacksplitdfa, DFA_START, str, n, &pos);
	if (!ACCEPT_TABLE(stacksplitdfa)[state])
		return NULL;

	return pos - 3;
}