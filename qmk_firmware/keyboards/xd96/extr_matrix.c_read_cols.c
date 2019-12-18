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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  IC1 ; 
 int /*<<< orphan*/  IC2 ; 
 int /*<<< orphan*/  PCA9555_PORT0 ; 
 int /*<<< orphan*/  PCA9555_PORT1 ; 
 int pca9555_readPins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t read_cols(void) {
  uint32_t state_1 = pca9555_readPins(IC2, PCA9555_PORT0);
  uint32_t state_2 = pca9555_readPins(IC2, PCA9555_PORT1);
  uint32_t state_3 = pca9555_readPins(IC1, PCA9555_PORT1);

  // For the XD96 the pins are mapped to port expanders as follows:
  //   all 8 pins port 0 IC2, first 6 pins port 1 IC2, first 4 pins port 1 IC1
  uint32_t state = (((state_3 & 0b00001111) << 14) | ((state_2 & 0b00111111) << 8) | state_1);
  return (~state) & 0b111111111111111111;
}