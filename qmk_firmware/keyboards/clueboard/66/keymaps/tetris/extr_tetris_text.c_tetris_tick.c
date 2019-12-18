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
 int /*<<< orphan*/  add_piece_to_board (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  board ; 
 scalar_t__ clear_lines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_piece_from_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int down_delay ; 
 int /*<<< orphan*/  draw_piece (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_piece_moved (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  empty_piece ; 
 scalar_t__ first_run ; 
 int game_over ; 
 int get_piece_min_y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_shape_char (int) ; 
 scalar_t__ is_piece_hitting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int myrandom (int) ; 
 scalar_t__ next_down ; 
 int /*<<< orphan*/  piece ; 
 int r ; 
 int rotation ; 
 int score ; 
 int /*<<< orphan*/  send_goto_xy (int,int) ; 
 int /*<<< orphan*/  set_piece (int /*<<< orphan*/ ,int,int) ; 
 int shape ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  temp_piece ; 
 int tetris_get_keypress () ; 
 int /*<<< orphan*/  tetris_send_down () ; 
 int /*<<< orphan*/  tetris_send_string (char*) ; 
 scalar_t__ time ; 
 int x ; 
 int y ; 

int tetris_tick(int ms_since_previous_tick) {
  if (game_over) {
    return 0;
  }
      
  time += ms_since_previous_tick;
  
  if (first_run || time > next_down) {
    if (first_run || is_piece_hitting(board, piece, x, y + 1)) {
      first_run = 0;
      add_piece_to_board(piece, board, x, y);

      score += clear_lines(board);

      down_delay = 500 - score * 10;
      if (down_delay < 100) {
        down_delay = 100;
      }
        
      rotation = 0;
      shape = r % 7;
      r = myrandom(r);
      set_piece(piece, shape, rotation);
      
      x = 1;
      y = - get_piece_min_y(piece);
      draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 0, 0);

      if (is_piece_hitting(board, piece, x, y)) {
        game_over = 1;
        send_goto_xy(12, 10);
        tetris_send_string(" game over");
        tetris_send_down();
        tetris_send_string(" score ");
        char tmp[10];
        sprintf(tmp, "%d", score);
        tetris_send_string(tmp);
        return 0;
      }
    } else {
      y++;
      draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 0, +1);
    }
    next_down = time + down_delay;
  } else {
      
    switch (tetris_get_keypress()) {
    case 1: { // up
      int oldrotation = rotation;
      rotation = (rotation + 1) % 4;
      copy_piece_from_to(piece, temp_piece);
      set_piece(piece, shape, rotation);
      if (is_piece_hitting(board, piece, x, y)) {
        rotation = oldrotation;
        set_piece(piece, shape, rotation);
      } else {
        draw_piece(get_shape_char(shape), 1 + x, y, temp_piece, piece);
      }
      break;
    }
    case 2: // left
      if (!is_piece_hitting(board, piece, x - 1, y)) {
        x--;
        draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, -1, 0);
      }
      break;
    case 3: {// down
      int starty = y;
      while (!is_piece_hitting(board, piece, x, y + 1)) {
        y++;
      }

      draw_piece(get_shape_char(shape), x + 1, starty, piece, empty_piece);
      draw_piece(get_shape_char(shape), x + 1, y, empty_piece, piece);

      next_down = time + down_delay;
      break;
    }
    case 4: // right
      if (!is_piece_hitting(board, piece, x + 1, y)) {
        x++;
        draw_piece_moved(get_shape_char(shape), 1 + x, y, piece, 1, 0);
      }
      break;
    }
  }
  return 1;
}