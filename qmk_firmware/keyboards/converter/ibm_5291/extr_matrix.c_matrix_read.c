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

/* Variables and functions */
 size_t MATRIX_COLS ; 
 size_t matrix_strobe (size_t) ; 
 int /*<<< orphan*/  select_col (size_t) ; 
 int /*<<< orphan*/  select_row (size_t) ; 

__attribute__((used)) static
bool matrix_read(uint8_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    uint8_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    select_row(current_row);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; ++col_index) {

        select_col(col_index) ;
        
        // strobe the matrix
        // Populate the matrix row with the state of the data pin
        current_matrix[current_row] |= matrix_strobe(col_index) ;
    }

    bool test = last_row_value != current_matrix[current_row] ;
    return test ;
}