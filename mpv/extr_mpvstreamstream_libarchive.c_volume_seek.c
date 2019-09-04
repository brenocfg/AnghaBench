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
struct mp_archive_volume {int seek_to; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int stream_seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool volume_seek(struct mp_archive_volume *vol)
{
    if (vol->seek_to < 0)
        return true;
    bool r = stream_seek(vol->src, vol->seek_to);
    vol->seek_to = -1;
    return r;
}