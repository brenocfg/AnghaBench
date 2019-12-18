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
 int checkTSPres () ; 
 int /*<<< orphan*/  writeDataToTS (int,int) ; 

uint8_t capSetup(void) {

  uint8_t temp_return = checkTSPres();

  if (temp_return == 1) {
    // Perform measurements every 16ms
    writeDataToTS(0x08, 1);

    // Increase detection integrator value
    writeDataToTS(0x0B, 1);

    // Oversample to gain two bits for columns
    writeDataToTS(0x28, 0x42);
    writeDataToTS(0x29, 0x00);
    writeDataToTS(0x2A, 0x00);
    writeDataToTS(0x2B, 0x00);
    writeDataToTS(0x2C, 0x42);
    writeDataToTS(0x2D, 0x00);
    writeDataToTS(0x2E, 0x00);
    writeDataToTS(0x2F, 0x00);
    writeDataToTS(0x30, 0x42);
    writeDataToTS(0x31, 0x42);
    writeDataToTS(0x32, 0x42);
    writeDataToTS(0x33, 0x42);

    // Recalibration if touch detected for more than 8 seconds n*0.16s
    writeDataToTS(0x0C, 50);

    // Enable keys and set key groups
    writeDataToTS(0x1C, 0x00 | 0x04);
    writeDataToTS(0x1D, 0x00 | 0x08);
    writeDataToTS(0x1E, 0x00 | 0x08);
    writeDataToTS(0x1F, 0x00 | 0x08);
    writeDataToTS(0x20, 0x00 | 0x04);
    writeDataToTS(0x21, 0x00 | 0x08);
    writeDataToTS(0x22, 0x00 | 0x08);
    writeDataToTS(0x23, 0x00 | 0x08);
    writeDataToTS(0x24, 0x00 | 0x04);
    writeDataToTS(0x25, 0x00 | 0x04);
    writeDataToTS(0x26, 0x00 | 0x04);
    writeDataToTS(0x27, 0x00 | 0x04);

  }
  return temp_return;
}