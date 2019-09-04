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
struct alsa_fmt {int mp_format; } ;

/* Variables and functions */
 struct alsa_fmt const* mp_alsa_formats ; 

__attribute__((used)) static const struct alsa_fmt *find_alsa_format(int mp_format)
{
    for (int n = 0; mp_alsa_formats[n].mp_format; n++) {
        if (mp_alsa_formats[n].mp_format == mp_format)
            return &mp_alsa_formats[n];
    }
    return NULL;
}