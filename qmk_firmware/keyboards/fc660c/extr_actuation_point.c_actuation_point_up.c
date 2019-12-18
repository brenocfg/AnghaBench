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
 scalar_t__ read_rdac () ; 
 int /*<<< orphan*/  write_rdac (scalar_t__) ; 

void actuation_point_up(void) {
    // write RDAC register: lower value makes actuation point shallow
    uint8_t rdac = read_rdac();
    if (rdac == 0)
        write_rdac(0);
    else
        write_rdac(rdac-1);
}