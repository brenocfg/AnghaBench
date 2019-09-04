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
struct timeline {int num_sources; struct demuxer** sources; int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; int /*<<< orphan*/  init_fragment; } ;
struct demuxer_params {int /*<<< orphan*/  init_fragment; } ;
struct demuxer {TYPE_1__* stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct timeline*,char*,char*) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct timeline*,struct demuxer**,int,struct demuxer*) ; 
 struct demuxer* demux_open_url (char*,struct demuxer_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct demuxer *open_source(struct timeline *tl, char *filename)
{
    for (int n = 0; n < tl->num_sources; n++) {
        struct demuxer *d = tl->sources[n];
        if (strcmp(d->stream->url, filename) == 0)
            return d;
    }
    struct demuxer_params params = {
        .init_fragment = tl->init_fragment,
    };
    struct demuxer *d = demux_open_url(filename, &params, tl->cancel, tl->global);
    if (d) {
        MP_TARRAY_APPEND(tl, tl->sources, tl->num_sources, d);
    } else {
        MP_ERR(tl, "EDL: Could not open source file '%s'.\n", filename);
    }
    return d;
}