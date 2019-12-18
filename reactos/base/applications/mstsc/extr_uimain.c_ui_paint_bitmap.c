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
typedef  int /*<<< orphan*/  uint8 ;
struct bitmap {int width; int height; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui_memblt (int,int,int,int,int,struct bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ui_paint_bitmap(int x, int y, int cx, int cy,
                int width, int height, uint8 * data)
{
  struct bitmap b;

  b.width = width;
  b.height = height;
  b.data = data;
  ui_memblt(12, x, y, cx, cy, &b, 0, 0);
}