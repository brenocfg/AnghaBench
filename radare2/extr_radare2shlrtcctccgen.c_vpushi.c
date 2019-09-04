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
struct TYPE_3__ {int i; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ CValue ;

/* Variables and functions */
 int /*<<< orphan*/  VT_CONST ; 
 int /*<<< orphan*/  int32_type ; 
 int /*<<< orphan*/  vsetc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void vpushi(int v) {
	CValue cval = { 0 };
	cval.i = v;
	vsetc (&int32_type, VT_CONST, &cval);
}