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
struct TYPE_6__ {int t; int /*<<< orphan*/ * ref; } ;
struct TYPE_5__ {unsigned long long ull; } ;
typedef  TYPE_1__ CValue ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 int /*<<< orphan*/  VT_CONST ; 
 int /*<<< orphan*/  vsetc (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void vpush64(int ty, unsigned long long v) {
	CValue cval;
	CType ctype;
	ctype.t = ty;
	ctype.ref = NULL;
	cval.ull = v;
	vsetc (&ctype, VT_CONST, &cval);
}