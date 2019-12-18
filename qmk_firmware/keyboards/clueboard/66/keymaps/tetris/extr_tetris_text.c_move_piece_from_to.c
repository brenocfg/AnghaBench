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

__attribute__((used)) static void move_piece_from_to(char from[7][7], char to[7][7], int xadd, int yadd) {
  for (int y = 0; y < 7; y++) {
    for (int x = 0; x < 7; x++) {
      if (x + xadd >= 0 && x + xadd < 7 && y + yadd >= 0 && y + yadd < 7) {
        to[y][x] = from[y + yadd][x + xadd];
      } else {
        to[y][x] = 0;
      }
    }
  }
}