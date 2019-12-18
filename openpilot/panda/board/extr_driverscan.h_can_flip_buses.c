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
 size_t* bus_lookup ; 
 size_t* can_num_lookup ; 

void can_flip_buses(uint8_t bus1, uint8_t bus2){
  bus_lookup[bus1] = bus2;
  bus_lookup[bus2] = bus1;
  can_num_lookup[bus1] = bus2;
  can_num_lookup[bus2] = bus1;
}