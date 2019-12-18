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

__attribute__((used)) static void rotate_piece(char piece[7][7]) {
  // transpose
  for (int y = 0; y < 7; y++) {
    for (int x = y + 1; x < 7; x++) {
      char tmp = piece[y][x];
      piece[y][x] = piece[x][y];
      piece[x][y] = tmp;
    }
  }

  // reverse rows
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 3; x++) {
      char tmp = piece[y][6 - x];
      piece[y][6 - x] = piece[y][x];
      piece[y][x] = tmp;
    }
  }
}