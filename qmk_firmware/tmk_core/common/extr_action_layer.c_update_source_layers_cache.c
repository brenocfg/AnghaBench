#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int col; int row; } ;
typedef  TYPE_1__ keypos_t ;

/* Variables and functions */
 int MATRIX_COLS ; 
 int MAX_LAYER_BITS ; 
 int** source_layers_cache ; 

void update_source_layers_cache(keypos_t key, uint8_t layer) {
    const uint8_t key_number  = key.col + (key.row * MATRIX_COLS);
    const uint8_t storage_row = key_number / 8;
    const uint8_t storage_bit = key_number % 8;

    for (uint8_t bit_number = 0; bit_number < MAX_LAYER_BITS; bit_number++) {
        source_layers_cache[storage_row][bit_number] ^= (-((layer & (1U << bit_number)) != 0) ^ source_layers_cache[storage_row][bit_number]) & (1U << storage_bit);
    }
}