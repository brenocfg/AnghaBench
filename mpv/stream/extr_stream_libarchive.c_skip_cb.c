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
struct mp_archive_volume {int /*<<< orphan*/  src; } ;
struct archive {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  stream_skip (int /*<<< orphan*/ ,int) ; 
 int stream_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  volume_seek (struct mp_archive_volume*) ; 

__attribute__((used)) static int64_t skip_cb(struct archive *arch, void *priv, int64_t request)
{
    struct mp_archive_volume *vol = priv;
    if (!volume_seek(vol))
        return -1;
    int64_t old = stream_tell(vol->src);
    stream_skip(vol->src, request);
    return stream_tell(vol->src) - old;
}