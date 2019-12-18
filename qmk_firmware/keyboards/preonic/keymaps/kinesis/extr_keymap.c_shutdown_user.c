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
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  tone_goodbye ; 

void shutdown_user()
{
  PLAY_SONG(tone_goodbye);
  _delay_ms(150);
  stop_all_notes();
}