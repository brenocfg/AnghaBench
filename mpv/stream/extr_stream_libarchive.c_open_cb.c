#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_archive_volume {int seek_to; scalar_t__ src; TYPE_2__* mpa; int /*<<< orphan*/  url; } ;
struct archive {int dummy; } ;
struct TYPE_4__ {TYPE_1__* primary_src; } ;
struct TYPE_3__ {int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  STREAM_READ ; 
 scalar_t__ stream_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stream_seek (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_cb(struct archive *arch, void *priv)
{
    struct mp_archive_volume *vol = priv;
    vol->seek_to = -1;
    if (!vol->src) {
        vol->src = stream_create(vol->url, STREAM_READ,
                                 vol->mpa->primary_src->cancel,
                                 vol->mpa->primary_src->global);
        return vol->src ? ARCHIVE_OK : ARCHIVE_FATAL;
    }

    // just rewind the primary stream
    return stream_seek(vol->src, 0) ? ARCHIVE_OK : ARCHIVE_FATAL;
}