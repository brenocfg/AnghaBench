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
 int /*<<< orphan*/  clear_piece (char**) ; 
 int /*<<< orphan*/  rotate_piece (char**) ; 

__attribute__((used)) static void set_piece(char piece[7][7], int shape, int rotation) {
  clear_piece(piece);
  switch (shape) {
  case 0:
    if (rotation % 2 == 0) {
      // xxXx
      piece[3][1] = 1;
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[3][4] = 1;
    } else {
      // x
      // x
      // X
      // x
      piece[1][3] = 1;
      piece[2][3] = 1;
      piece[3][3] = 1;
      piece[4][3] = 1;
    }
    break;
  case 1:
    // xXx
    //   x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][4] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 2:
    // xXx
    // x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][2] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 3:
    // xX
    // xx
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[4][2] = 1;
    piece[4][3] = 1;
    break;
  case 4:
    if (rotation % 2 == 0) {
      // xX
      //  xx
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[4][3] = 1;
      piece[4][4] = 1;
    } else {
      //  x
      // xX
      // x
      piece[2][3] = 1;
      piece[3][2] = 1;
      piece[3][3] = 1;
      piece[4][2] = 1;
    }
    break;
  case 5:
    // xXx
    //  x
    piece[3][2] = 1;
    piece[3][3] = 1;
    piece[3][4] = 1;
    piece[4][3] = 1;
    for (int i = 0; i < rotation; i++) {
      rotate_piece(piece);
    }
    break;
  case 6:
    if (rotation % 2 == 0) {
      //  Xx
      // xx
      piece[3][3] = 1;
      piece[3][4] = 1;
      piece[4][2] = 1;
      piece[4][3] = 1;
    } else {
      // x
      // Xx
      //  x
      piece[2][3] = 1;
      piece[3][3] = 1;
      piece[3][4] = 1;
      piece[4][4] = 1;
    }
    break;
  }
}