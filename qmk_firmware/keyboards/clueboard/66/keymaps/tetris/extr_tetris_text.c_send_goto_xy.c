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
 int /*<<< orphan*/  tetris_send_down () ; 
 int /*<<< orphan*/  tetris_send_left () ; 
 int /*<<< orphan*/  tetris_send_right () ; 
 int /*<<< orphan*/  tetris_send_up () ; 

__attribute__((used)) static void send_goto_xy(int x, int y) {
  while (curx < x) {
    tetris_send_right();
    curx++;
  }
  while (curx > x) {
    tetris_send_left();
    curx--;
  }
  while (cury < y) {
    tetris_send_down();
    cury++;
  }
  while (cury > y) {
    tetris_send_up();
    cury--;
  }
}