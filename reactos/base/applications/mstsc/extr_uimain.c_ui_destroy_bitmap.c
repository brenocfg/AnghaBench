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
struct bitmap {struct bitmap* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct bitmap*) ; 

void
ui_destroy_bitmap(void * bmp)
{
  struct bitmap * b;

  b = (struct bitmap *) bmp;
  if (b != 0)
  {
    xfree(b->data);
  }
  xfree(b);
}