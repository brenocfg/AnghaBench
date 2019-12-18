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

/* Variables and functions */
 int NUM_LINKS ; 
 int /*<<< orphan*/  init_byte_stuffer_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * states ; 

void init_byte_stuffer(void) {
    int i;
    for (i = 0; i < NUM_LINKS; i++) {
        init_byte_stuffer_state(&states[i]);
    }
}