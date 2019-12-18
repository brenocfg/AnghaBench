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
struct TYPE_6__ {int /*<<< orphan*/  bbs; int /*<<< orphan*/  ends; int /*<<< orphan*/  size; int /*<<< orphan*/  score; } ;
typedef  TYPE_1__ fcn_t ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ start; scalar_t__ end; scalar_t__ score; } ;
typedef  TYPE_2__ bb_t ;

/* Variables and functions */
 scalar_t__ END ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static bool fcnAddBB (fcn_t *fcn, bb_t* block) {
	if (!fcn) {
		eprintf ("No function given to add a basic block\n");
		return false;
	}
	fcn->score += block->score;
	fcn->size += block->end - block->start;
	if (block->type == END) {
		fcn->ends++;
	}
	if (!fcn->bbs) {
		eprintf ("Block list not initialized\n");
		return false;
	}
	r_list_append (fcn->bbs, block);
	return true;
}