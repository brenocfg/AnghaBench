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
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ RANode ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W (char*) ; 

__attribute__((used)) static void tiny_RANode_print(const RAGraph *g, const RANode *n, int cur) {
	G (n->x, n->y);
	if (cur) {
		W ("##");
	} else {
		W ("()");
	}
}