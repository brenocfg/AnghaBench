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
typedef  int /*<<< orphan*/  TokenAuxData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 size_t MAX_PUSHBACKS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 size_t num_pushbacks ; 
 int /*<<< orphan*/ * pushback_auxdata ; 
 int* pushback_token ; 

__attribute__((used)) static void
push_back_token(int token, TokenAuxData *auxdata)
{
	if (num_pushbacks >= MAX_PUSHBACKS)
		elog(ERROR, "too many tokens pushed back");
	pushback_token[num_pushbacks] = token;
	pushback_auxdata[num_pushbacks] = *auxdata;
	num_pushbacks++;
}