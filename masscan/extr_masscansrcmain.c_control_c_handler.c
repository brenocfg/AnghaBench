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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int is_rx_done ; 
 unsigned int is_tx_done ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void control_c_handler(int x)
{
    static unsigned control_c_pressed = 0;
    static unsigned control_c_pressed_again = 0;
    if (control_c_pressed == 0) {
        fprintf(stderr,
                "waiting several seconds to exit..."
                "                                            \n"
                );
        fflush(stderr);
        control_c_pressed = 1+x;
        is_tx_done = control_c_pressed;
    } else {
        if (is_rx_done) {
            fprintf(stderr, "\nERROR: threads not exiting %d\n", is_rx_done);
            if (is_rx_done++ > 1)
                exit(1);
        } else {
            control_c_pressed_again = 1;
            is_rx_done = control_c_pressed_again;
        }
    }

}