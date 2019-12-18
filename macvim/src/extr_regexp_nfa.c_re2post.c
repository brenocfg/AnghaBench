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
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ) ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  NFA_MOPEN ; 
 int /*<<< orphan*/  REG_NOPAREN ; 
 scalar_t__ nfa_reg (int /*<<< orphan*/ ) ; 
 int* post_start ; 

__attribute__((used)) static int *
re2post()
{
    if (nfa_reg(REG_NOPAREN) == FAIL)
	return NULL;
    EMIT(NFA_MOPEN);
    return post_start;
}