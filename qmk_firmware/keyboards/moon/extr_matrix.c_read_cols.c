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
typedef  int uint16_t ;

/* Variables and functions */
 int COLS_MASK ; 
 int /*<<< orphan*/  IC2 ; 
 int /*<<< orphan*/  PCA9555_PORT0 ; 
 int /*<<< orphan*/  PCA9555_PORT1 ; 
 int PORT0_COLS_MASK ; 
 int PORT1_COLS_MASK ; 
 int pca9555_readPins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t read_cols(void) {
  uint16_t state_1 = pca9555_readPins(IC2, PCA9555_PORT0);
  uint16_t state_2 = pca9555_readPins(IC2, PCA9555_PORT1);

  uint16_t state = ((state_1 & PORT0_COLS_MASK) << 3) | ((state_2 & PORT1_COLS_MASK));

  // A low pin indicates an active column
  return (~state) & COLS_MASK;
}