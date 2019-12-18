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
struct ff_decoder {int /*<<< orphan*/  refresh_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_timer_schedule (int /*<<< orphan*/ *,int) ; 

void ff_decoder_schedule_refresh(struct ff_decoder *decoder, int delay)
{
	ff_timer_schedule(&decoder->refresh_timer, 1000 * delay);
}