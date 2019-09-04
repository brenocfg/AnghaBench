#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_value; } ;
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {int /*<<< orphan*/  lineswidth; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */

__attribute__((used)) static int cb_asmlineswidth(void *user, void *data) {
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	core->anal->lineswidth = node->i_value;
	return true;
}