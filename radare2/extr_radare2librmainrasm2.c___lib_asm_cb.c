#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  a; } ;
typedef  int /*<<< orphan*/  RLibPlugin ;
typedef  TYPE_1__ RAsmState ;
typedef  int /*<<< orphan*/  RAsmPlugin ;

/* Variables and functions */
 int /*<<< orphan*/  r_asm_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __lib_asm_cb(RLibPlugin *pl, void *user, void *data) {
	RAsmPlugin *hand = (RAsmPlugin *)data;
	RAsmState *as = (RAsmState *)user;
	r_asm_add (as->a, hand);
	return true;
}