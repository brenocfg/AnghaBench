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
 int /*<<< orphan*/  draw_piece (char,int,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  move_piece_from_to (char**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  temp_piece ; 

__attribute__((used)) static void draw_piece_moved(char c, int x, int y, char piece[7][7], int oldxadd, int oldyadd) {
  move_piece_from_to(piece, temp_piece, oldxadd, oldyadd);
  draw_piece(c, x, y, temp_piece, piece);
}