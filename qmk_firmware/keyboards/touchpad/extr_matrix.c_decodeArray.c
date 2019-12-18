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
typedef  int uint16_t ;

/* Variables and functions */
 int* SENc ; 
 int* SENr ; 

void decodeArray(uint16_t dataIn, uint8_t *column, uint8_t *row) {
  uint8_t i1 = 20, i2 = 20;
  for (uint8_t i = 0; i < 12; i++) {
    if ((dataIn & 0b1) == 1) {
      if (i1 == 20) {
        i1 = i;
      } else if (i2 == 20) {
        i2 = i;
      }
    }
    dataIn = dataIn >> 1;
  }

  for (uint8_t j = 0; j < 6; j++) {
    if (SENr[j] == i1 || SENr[j] == i2) {
      *row = j;
    }
    if (SENc[j] == i1 || SENc[j] == i2) {
      *column = j;
    }
  }
}