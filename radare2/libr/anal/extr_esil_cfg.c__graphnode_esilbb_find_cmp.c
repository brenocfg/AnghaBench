#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ off; scalar_t__ idx; } ;
struct TYPE_6__ {scalar_t__ off; scalar_t__ idx; } ;
struct TYPE_10__ {TYPE_2__ last; TYPE_1__ first; } ;
struct TYPE_9__ {scalar_t__ off; scalar_t__ idx; } ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__ RGraphNode ;
typedef  TYPE_4__ RAnalEsilEOffset ;
typedef  TYPE_5__ RAnalEsilBB ;

/* Variables and functions */

__attribute__((used)) static int _graphnode_esilbb_find_cmp(void *incoming, void *in, void *user) {
	RAnalEsilEOffset *find_me = (RAnalEsilEOffset *)incoming;
	RGraphNode *in_gnode = (RGraphNode *)in;
	RAnalEsilBB *in_bb = (RAnalEsilBB *)in_gnode->data;
	// not sure if this is needed that way
	if (find_me->off < in_bb->first.off) {
		return -1;
	}
	if (find_me->off > in_bb->last.off) {
		return 1;
	}
	if (find_me->idx < in_bb->first.idx) {
		return -1;
	}
	if (find_me->idx > in_bb->last.idx) {
		return 1;
	}
	return 0;
}