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
 scalar_t__* chord ; 
 int /*<<< orphan*/  virtser_send (scalar_t__) ; 

__attribute__((used)) static void send_steno_state(uint8_t size, bool send_empty) {
    for (uint8_t i = 0; i < size; ++i) {
        if (chord[i] || send_empty) {
            virtser_send(chord[i]);
        }
    }
}