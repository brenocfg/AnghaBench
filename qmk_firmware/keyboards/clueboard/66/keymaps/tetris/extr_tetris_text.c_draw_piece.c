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

/* Variables and functions */
 int /*<<< orphan*/  draw_row (char,char*,char*,int,int) ; 

__attribute__((used)) static void draw_piece(char c, int x, int y, char oldpiece[7][7], char piece[7][7]) {
  for (int py = 0; py < 7; py++) {
    draw_row(c, oldpiece[py], piece[py], x, y + py);
  }
}