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
 int OpenDrain ; 
 int /*<<< orphan*/  P0_8 ; 
 int PullNone ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  gpio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_mode (int /*<<< orphan*/ *,int) ; 

void data_init(void) {
    gpio_init(&data, P0_8);
    gpio_mode(&data, OpenDrain | PullNone);
}