#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block_flags_stat_t {int from; int step; TYPE_2__* as; } ;
struct TYPE_7__ {int offset; } ;
struct TYPE_6__ {TYPE_1__* block; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ RFlagItem ;

/* Variables and functions */

__attribute__((used)) static bool block_flags_stat(RFlagItem *fi, void *user) {
	struct block_flags_stat_t *u = (struct block_flags_stat_t *)user;
	int piece = (fi->offset - u->from) / u->step;
	u->as->block[piece].flags++;
	return true;
}