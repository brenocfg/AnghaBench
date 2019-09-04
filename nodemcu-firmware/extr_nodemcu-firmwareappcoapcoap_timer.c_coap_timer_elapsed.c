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
typedef  scalar_t__ coap_tick_t ;

/* Variables and functions */
 scalar_t__ SYS_TIME_MAX ; 
 scalar_t__ basetime ; 
 int system_get_time () ; 

void coap_timer_elapsed(coap_tick_t *diff){
  coap_tick_t now = system_get_time() / 1000;   // coap_tick_t is in ms. also sys_timer
  if(now>=basetime){
    *diff = now-basetime;
  } else {
    *diff = now + SYS_TIME_MAX -basetime;
  }
  basetime = now;
}