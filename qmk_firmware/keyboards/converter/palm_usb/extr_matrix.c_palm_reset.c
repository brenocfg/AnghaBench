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
 int /*<<< orphan*/  last_activity ; 
 scalar_t__ palm_handshake () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  rts_reset () ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t palm_reset(void) {
    print("@");
    rts_reset();  // shouldn't need to power cycle. 

    if ( palm_handshake() ) {
        last_activity = timer_read();
        return 1;
    } else { 
        print("failed reset");
        return 0;
    }

}