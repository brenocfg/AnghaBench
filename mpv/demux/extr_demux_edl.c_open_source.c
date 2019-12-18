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
struct timeline_par {int num_parts; int /*<<< orphan*/  init_fragment; TYPE_1__* parts; } ;
struct timeline {int /*<<< orphan*/  num_sources; int /*<<< orphan*/  sources; int /*<<< orphan*/  global; int /*<<< orphan*/  cancel; } ;
struct demuxer_params {int /*<<< orphan*/  init_fragment; } ;
struct demuxer {TYPE_2__* stream; } ;
struct TYPE_4__ {int /*<<< orphan*/  url; } ;
struct TYPE_3__ {struct demuxer* source; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct timeline*,char*,char*) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct demuxer*) ; 
 struct demuxer* demux_open_url (char*,struct demuxer_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct demuxer *open_source(struct timeline *root,
                                   struct timeline_par *tl, char *filename)
{
    for (int n = 0; n < tl->num_parts; n++) {
        struct demuxer *d = tl->parts[n].source;
        if (d && strcmp(d->stream->url, filename) == 0)
            return d;
    }
    struct demuxer_params params = {
        .init_fragment = tl->init_fragment,
    };
    struct demuxer *d = demux_open_url(filename, &params, root->cancel,
                                       root->global);
    if (d) {
        MP_TARRAY_APPEND(root, root->sources, root->num_sources, d);
    } else {
        MP_ERR(root, "EDL: Could not open source file '%s'.\n", filename);
    }
    return d;
}