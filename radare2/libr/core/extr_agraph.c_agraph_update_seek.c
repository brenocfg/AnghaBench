#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int force_update_seek; int /*<<< orphan*/ * update_seek_on; } ;
typedef  int /*<<< orphan*/  RANode ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */

__attribute__((used)) static void agraph_update_seek(RAGraph *g, RANode *n, int force) {
	g->update_seek_on = n;
	g->force_update_seek = force;
}