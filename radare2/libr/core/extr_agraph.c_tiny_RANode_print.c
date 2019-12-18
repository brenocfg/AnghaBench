#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {scalar_t__ use_utf8; } ;
typedef  TYPE_1__ RCons ;
typedef  TYPE_2__ RANode ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* UTF_CIRCLE ; 
 int /*<<< orphan*/  W (char*) ; 
 TYPE_1__* r_cons_singleton () ; 

__attribute__((used)) static void tiny_RANode_print(const RAGraph *g, const RANode *n, int cur) {
	G (n->x, n->y);
	RCons *cons = r_cons_singleton ();
	char *circle = cons->use_utf8 ? UTF_CIRCLE :"()";
	if (cur) {
		W ("##");
	} else {
		W (circle);
	}
}