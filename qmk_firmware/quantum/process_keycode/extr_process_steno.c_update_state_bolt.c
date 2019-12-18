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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 size_t TXB_GET_GROUP (scalar_t__) ; 
 scalar_t__ boltmap ; 
 scalar_t__* chord ; 
 scalar_t__ pgm_read_byte (scalar_t__) ; 
 scalar_t__* state ; 

__attribute__((used)) static bool update_state_bolt(uint8_t key, bool press) {
    uint8_t boltcode = pgm_read_byte(boltmap + key);
    if (press) {
        state[TXB_GET_GROUP(boltcode)] |= boltcode;
        chord[TXB_GET_GROUP(boltcode)] |= boltcode;
    } else {
        state[TXB_GET_GROUP(boltcode)] &= ~boltcode;
    }
    return false;
}