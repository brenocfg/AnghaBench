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
typedef  scalar_t__ matrix_row_t ;

/* Variables and functions */
 scalar_t__ read_cols () ; 
 int /*<<< orphan*/  select_row (size_t) ; 
 int /*<<< orphan*/  wait_us (int) ; 

__attribute__((used)) static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Clear data in matrix row
  current_matrix[current_row] = 0;

  // Select row and wait for row selection to stabilize
  select_row(current_row);
  wait_us(30);

  current_matrix[current_row] = read_cols();

  // No need to Unselect row as the next `select_row` will blank everything

  return (last_row_value != current_matrix[current_row]);
}