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
struct TYPE_3__ {int /*<<< orphan*/  frame_hwnd; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DocHostContainer_get_docobj_rect(DocHost *This, RECT *rc)
{
    GetClientRect(This->frame_hwnd, rc);
}