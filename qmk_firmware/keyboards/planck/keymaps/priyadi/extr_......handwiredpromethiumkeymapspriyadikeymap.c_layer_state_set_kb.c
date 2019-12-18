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
typedef  unsigned long uint32_t ;

/* Variables and functions */
 unsigned long _EMOJI ; 
 unsigned long _EMPTY ; 
 unsigned long _FUN ; 
 unsigned long _GREEKL ; 
 unsigned long _GREEKU ; 
 unsigned long _NUM ; 
 unsigned long _PUNC ; 

uint32_t layer_state_set_kb(uint32_t state)
{
  // turn on punc layer if both fun & num are on
  if ((state & ((1UL<<_NUM) | (1UL<<_FUN))) == ((1UL<<_NUM) | (1UL<<_FUN))) {
    state |= (1UL<<_PUNC);
  } else {
    state &= ~(1UL<<_PUNC);
  }

  // turn on emoji layer if empty and greek layer are on
  if (
    (state & ((1UL<<_EMPTY) | (1UL<<_GREEKU))) == ((1UL<<_EMPTY) | (1UL<<_GREEKU))
    || (state & ((1UL<<_EMPTY) | (1UL<<_GREEKL))) == ((1UL<<_EMPTY) | (1UL<<_GREEKL))
  ) {
    state |= (1UL<<_EMOJI);
  } else {
    state &= ~(1UL<<_EMOJI);
  }
  return state;
}