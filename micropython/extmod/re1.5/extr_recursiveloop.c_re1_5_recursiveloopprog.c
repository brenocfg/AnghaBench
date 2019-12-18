#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  insts; } ;
struct TYPE_6__ {int /*<<< orphan*/  begin; } ;
typedef  TYPE_1__ Subject ;
typedef  TYPE_2__ ByteProg ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_ANCHORED (int /*<<< orphan*/ ,int) ; 
 int recursiveloop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char const**,int) ; 

int
re1_5_recursiveloopprog(ByteProg *prog, Subject *input, const char **subp, int nsubp, int is_anchored)
{
	return recursiveloop(HANDLE_ANCHORED(prog->insts, is_anchored), input->begin, input, subp, nsubp);
}