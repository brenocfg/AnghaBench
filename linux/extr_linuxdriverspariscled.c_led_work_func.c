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
struct work_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ cpu_type; } ;

/* Variables and functions */
 unsigned long HEARTBEAT_2ND_RANGE_END ; 
 unsigned long HEARTBEAT_2ND_RANGE_START ; 
 unsigned long HEARTBEAT_LEN ; 
 unsigned long HZ ; 
 unsigned char LED4 ; 
 unsigned char LED5 ; 
 unsigned char LED6 ; 
 unsigned char LED7 ; 
 unsigned char LED_HEARTBEAT ; 
 int /*<<< orphan*/  LED_UPDATE_INTERVAL ; 
 TYPE_1__ boot_cpu_data ; 
 unsigned long jiffies ; 
 unsigned char lastleds ; 
 int /*<<< orphan*/  led_diskio ; 
 int /*<<< orphan*/  led_func_ptr (unsigned char) ; 
 unsigned char led_get_diskio_activity () ; 
 unsigned char led_get_net_activity () ; 
 int /*<<< orphan*/  led_heartbeat ; 
 int /*<<< orphan*/  led_lanrxtx ; 
 int /*<<< orphan*/  led_task ; 
 int /*<<< orphan*/  led_wq ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oops_in_progress ; 
 scalar_t__ pcxl2 ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void led_work_func (struct work_struct *unused)
{
	static unsigned long last_jiffies;
	static unsigned long count_HZ; /* counter in range 0..HZ */
	unsigned char currentleds = 0; /* stores current value of the LEDs */

	/* exit if not initialized */
	if (!led_func_ptr)
	    return;

	/* increment the heartbeat timekeeper */
	count_HZ += jiffies - last_jiffies;
	last_jiffies = jiffies;
	if (count_HZ >= HZ)
	    count_HZ = 0;

	if (likely(led_heartbeat))
	{
		/* flash heartbeat-LED like a real heart
		 * (2 x short then a long delay)
		 */
		if (count_HZ < HEARTBEAT_LEN || 
				(count_HZ >= HEARTBEAT_2ND_RANGE_START &&
				count_HZ < HEARTBEAT_2ND_RANGE_END)) 
			currentleds |= LED_HEARTBEAT;
	}

	if (likely(led_lanrxtx))  currentleds |= led_get_net_activity();
	if (likely(led_diskio))   currentleds |= led_get_diskio_activity();

	/* blink LEDs if we got an Oops (HPMC) */
	if (unlikely(oops_in_progress)) {
		if (boot_cpu_data.cpu_type >= pcxl2) {
			/* newer machines don't have loadavg. LEDs, so we
			 * let all LEDs blink twice per second instead */
			currentleds = (count_HZ <= (HZ/2)) ? 0 : 0xff;
		} else {
			/* old machines: blink loadavg. LEDs twice per second */
			if (count_HZ <= (HZ/2))
				currentleds &= ~(LED4|LED5|LED6|LED7);
			else
				currentleds |= (LED4|LED5|LED6|LED7);
		}
	}

	if (currentleds != lastleds)
	{
		led_func_ptr(currentleds);	/* Update the LCD/LEDs */
		lastleds = currentleds;
	}

	queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL);
}