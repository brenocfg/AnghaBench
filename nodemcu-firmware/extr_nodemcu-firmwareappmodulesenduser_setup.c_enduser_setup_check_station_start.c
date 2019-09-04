#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  check_station_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  enduser_setup_check_station ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* state ; 

__attribute__((used)) static void enduser_setup_check_station_start(void)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_check_station_start");

  os_timer_setfn(&(state->check_station_timer), enduser_setup_check_station, NULL);
  SWTIMER_REG_CB(enduser_setup_check_station, SWTIMER_RESUME);
    //The function enduser_setup_check_station checks for a successful connection to the configured AP
    //My guess: I'm not sure about whether or not user feedback is given via the web interface, but I don't see a problem with letting this timer resume.
  os_timer_arm(&(state->check_station_timer), 3*1000, TRUE);
}