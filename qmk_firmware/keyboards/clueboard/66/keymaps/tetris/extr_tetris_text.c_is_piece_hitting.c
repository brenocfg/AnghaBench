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

__attribute__((used)) static int is_piece_hitting(char board[20][10], char piece[7][7], int x, int y) {
  for (int py = 0; py < 7; py++) {
    for (int px = 0; px < 7; px++) {
      if (piece[py][px] &&
          (px + x >= 10 || px + x < 0
           || py + y >= 20 || py + y < 0
           || board[py + y][px + x])) {
        return 1;
      }
    }
  }
  return 0;
}