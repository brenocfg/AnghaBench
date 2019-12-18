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
 int /*<<< orphan*/  IC2 ; 
 int /*<<< orphan*/  PCA9555_PORT0 ; 
 int /*<<< orphan*/  PCA9555_PORT1 ; 
 int pca9555_readPins (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t read_cols(void) {
  uint16_t state_1 = pca9555_readPins(IC2, PCA9555_PORT0);
  uint16_t state_2 = pca9555_readPins(IC2, PCA9555_PORT1);

  // For the XD84 all cols are on the same IC and mapped sequentially
  // while this technically gives 16 column reads,
  // the 16th column can never be set so is safely ignored
  return ~((state_2 << 8) | state_1);
}