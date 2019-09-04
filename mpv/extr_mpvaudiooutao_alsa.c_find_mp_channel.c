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
 int MP_SPEAKER_ID_COUNT ; 
 int** alsa_to_mp_channels ; 

__attribute__((used)) static int find_mp_channel(int alsa_channel)
{
    for (int i = 0; alsa_to_mp_channels[i][1] != MP_SPEAKER_ID_COUNT; i++) {
        if (alsa_to_mp_channels[i][0] == alsa_channel)
            return alsa_to_mp_channels[i][1];
    }

    return MP_SPEAKER_ID_COUNT;
}