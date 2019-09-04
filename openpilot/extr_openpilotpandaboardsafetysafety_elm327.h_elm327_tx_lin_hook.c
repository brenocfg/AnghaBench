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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int elm327_tx_lin_hook(int lin_num, uint8_t *data, int len) {
  if(lin_num != 0) return false; //Only operate on LIN 0, aka serial 2
  if(len < 5 || len > 11) return false; //Valid KWP size
  if(!((data[0] & 0xF8) == 0xC0 && (data[0] & 0x07) > 0 &&
       data[1] == 0x33 && data[2] == 0xF1)) return false; //Bad msg
  return true;
}