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
 int ALL_HIGH ; 
 int ALL_INPUT ; 
 int /*<<< orphan*/  IC1 ; 
 int /*<<< orphan*/  PCA9555_PORT0 ; 
 int /*<<< orphan*/  pca9555_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pca9555_set_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void select_row(uint8_t row) {
  // For the XD96 all rows are on the same IC and port
  // so its safe enough to assume here row == pin
  uint8_t pin = row;
  uint8_t mask = 1 << pin;

  pca9555_set_output(IC1, PCA9555_PORT0, ALL_HIGH & (~mask));
  pca9555_set_config(IC1, PCA9555_PORT0, ALL_INPUT & (~mask));
}