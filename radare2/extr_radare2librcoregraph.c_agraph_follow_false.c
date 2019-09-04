#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  curnode; } ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  agraph_update_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  follow_nth (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_anode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void agraph_follow_false(RAGraph *g) {
	follow_nth (g, 1);
	agraph_update_seek (g, get_anode (g->curnode), false);
}