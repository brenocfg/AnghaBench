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
typedef  int /*<<< orphan*/  RPanelPos ;

/* Variables and functions */
 int /*<<< orphan*/  __set_pos (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  __set_size (int /*<<< orphan*/ *,int,int) ; 

void __set_geometry(RPanelPos *pos, int x, int y, int w, int h) {
	__set_pos (pos, x, y);
	__set_size (pos, w, h);
}