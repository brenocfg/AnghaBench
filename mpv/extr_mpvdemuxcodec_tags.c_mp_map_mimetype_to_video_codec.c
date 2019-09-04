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
 char const*** mimetype_to_codec ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 

const char *mp_map_mimetype_to_video_codec(const char *mimetype)
{
    if (mimetype) {
        for (int n = 0; mimetype_to_codec[n][0]; n++) {
            if (strcasecmp(mimetype_to_codec[n][0], mimetype) == 0)
                return mimetype_to_codec[n][1];
        }
    }
    return NULL;
}