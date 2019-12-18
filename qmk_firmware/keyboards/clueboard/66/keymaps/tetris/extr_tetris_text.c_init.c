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
 int curx ; 
 int cury ; 
 int /*<<< orphan*/  draw_board_line () ; 
 int /*<<< orphan*/  tetris_send_string (char*) ; 

__attribute__((used)) static void init(void) {
  for (int i = 0; i < 20; i++) {
    draw_board_line();
  }
  tetris_send_string("doooooooooob");
  curx = 12;
  cury = 20;
}