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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 size_t MATRIX_COLS ; 
 size_t MATRIX_ROWS ; 
 size_t _BASE ; 
 int /*<<< orphan*/ *** keymaps ; 
 scalar_t__ pgm_read_word (int /*<<< orphan*/ *) ; 

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}