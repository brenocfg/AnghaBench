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
 scalar_t__ M0110_ERROR ; 
 scalar_t__ M0110_NULL ; 
 scalar_t__ debug_enable ; 
 int is_modified ; 
 scalar_t__ m0110_recv_key () ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  phex (scalar_t__) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  register_key (scalar_t__) ; 

uint8_t matrix_scan(void)
{
    uint8_t key;

    is_modified = false;
    key = m0110_recv_key();

    if (key == M0110_NULL) {
        return 0;
    } else if (key == M0110_ERROR) {
        return 0;
    } else {
        is_modified = true;
        register_key(key);
    }

    if (debug_enable) {
        print("["); phex(key); print("]\n");
    }
    
    matrix_scan_quantum();
    return 1;
}