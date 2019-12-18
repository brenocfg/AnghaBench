#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float radius; float feather; void* outerColor; void* innerColor; int /*<<< orphan*/  xform; } ;
typedef  TYPE_1__ NVGpaint ;
typedef  void* NVGcolor ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvgTransformIdentity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvg__setPaintColor(NVGpaint* p, NVGcolor color)
{
	memset(p, 0, sizeof(*p));
	nvgTransformIdentity(p->xform);
	p->radius = 0.0f;
	p->feather = 1.0f;
	p->innerColor = color;
	p->outerColor = color;
}