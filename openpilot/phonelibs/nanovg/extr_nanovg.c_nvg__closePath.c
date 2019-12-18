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
struct TYPE_3__ {int closed; } ;
typedef  TYPE_1__ NVGpath ;
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 TYPE_1__* nvg__lastPath (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvg__closePath(NVGcontext* ctx)
{
	NVGpath* path = nvg__lastPath(ctx);
	if (path == NULL) return;
	path->closed = 1;
}