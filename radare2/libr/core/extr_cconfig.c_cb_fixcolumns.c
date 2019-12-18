#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fix_columns; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_cons_singleton () ; 

__attribute__((used)) static bool cb_fixcolumns(void *user, void *data) {
	RConfigNode *node = (RConfigNode *) data;
	r_cons_singleton ()->fix_columns = atoi (node->value);
	return true;
}