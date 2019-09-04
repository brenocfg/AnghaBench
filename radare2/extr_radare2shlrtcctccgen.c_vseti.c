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
struct TYPE_3__ {int /*<<< orphan*/ * ref; int /*<<< orphan*/  t; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ CType ;

/* Variables and functions */
 int /*<<< orphan*/  VT_INT32 ; 
 int /*<<< orphan*/  vset (TYPE_1__*,int,int) ; 

__attribute__((used)) static void vseti(int r, int v) {
	CType type = { 0 };
	type.t = VT_INT32;
	type.ref = NULL;
	vset (&type, r, v);
}