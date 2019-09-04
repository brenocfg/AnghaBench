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
struct archive {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int stream_get_size (int /*<<< orphan*/ ) ; 
 int stream_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t seek_cb(struct archive *arch, void *priv,
                       int64_t offset, int whence)
{
    struct mp_archive_volume *vol = priv;
    switch (whence) {
    case SEEK_SET:
        vol->seek_to = offset;
        break;
    case SEEK_CUR:
        if (vol->seek_to < 0)
            vol->seek_to = stream_tell(vol->src);
        vol->seek_to += offset;
        break;
    case SEEK_END: ;
        int64_t size = stream_get_size(vol->src);
        if (size < 0)
            return -1;
        vol->seek_to = size + offset;
        break;
    default:
        return -1;
    }
    return vol->seek_to;
}