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
struct TYPE_2__ {int /*<<< orphan*/  raw; scalar_t__ enable; } ;

/* Variables and functions */
 TYPE_1__ audio_config ; 
 int /*<<< orphan*/  eeconfig_update_audio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_all_notes () ; 

void audio_off(void) {
    stop_all_notes();
    audio_config.enable = 0;
    eeconfig_update_audio(audio_config.raw);
}