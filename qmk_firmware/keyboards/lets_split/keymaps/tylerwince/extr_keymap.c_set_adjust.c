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
 int /*<<< orphan*/  rgblight_sethsv_master (int,int,int) ; 
 int /*<<< orphan*/  rgblight_sethsv_slave (int,int,int) ; 

void set_adjust(void){
  rgblight_sethsv_slave(35, 255, 255);
  rgblight_sethsv_master(255, 255, 255);
}