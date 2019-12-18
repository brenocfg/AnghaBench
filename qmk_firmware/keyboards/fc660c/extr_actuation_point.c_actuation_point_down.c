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
 int read_rdac () ; 
 int /*<<< orphan*/  write_rdac (int) ; 

void actuation_point_down(void) {
    // write RDAC register: higher value makes actuation point deep
    uint8_t rdac = read_rdac();
    if (rdac == 63)
        write_rdac(63);
    else
        write_rdac(rdac+1);
}