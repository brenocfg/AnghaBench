#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  s_cursor_visible ; 

__attribute__((used)) static void
cursor_visible(BOOL fVisible)
{
    s_cursor_visible = fVisible;
#ifdef MCH_CURSOR_SHAPE
    mch_update_cursor();
#endif
}