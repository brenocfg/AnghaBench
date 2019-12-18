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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 int MP_SPEAKER_ID_COUNT ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 scalar_t__** speaker_names ; 
 scalar_t__** std_layout_names ; 

void mp_chmap_print_help(struct mp_log *log)
{
    mp_info(log, "Speakers:\n");
    for (int n = 0; n < MP_SPEAKER_ID_COUNT; n++) {
        if (speaker_names[n][0])
            mp_info(log, "    %-16s (%s)\n",
                    speaker_names[n][0], speaker_names[n][1]);
    }
    mp_info(log, "Standard layouts:\n");
    for (int n = 0; std_layout_names[n][0]; n++) {
        mp_info(log, "    %-16s (%s)\n",
                 std_layout_names[n][0], std_layout_names[n][1]);
    }
    for (int n = 0; n < MP_NUM_CHANNELS; n++)
        mp_info(log, "    unknown%d\n", n + 1);
}