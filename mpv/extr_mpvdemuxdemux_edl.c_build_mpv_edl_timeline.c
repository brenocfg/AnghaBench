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
struct tl_parts {int dummy; } ;
struct timeline {TYPE_1__* demuxer; int /*<<< orphan*/  num_sources; int /*<<< orphan*/  sources; } ;
struct priv {int /*<<< orphan*/  allow_any; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  filename; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct timeline*,char*) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  build_timeline (struct timeline*,struct tl_parts*) ; 
 int /*<<< orphan*/  fix_filenames (struct tl_parts*,int /*<<< orphan*/ ) ; 
 struct tl_parts* parse_edl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct tl_parts*) ; 

__attribute__((used)) static void build_mpv_edl_timeline(struct timeline *tl)
{
    struct priv *p = tl->demuxer->priv;

    struct tl_parts *parts = parse_edl(p->data);
    if (!parts) {
        MP_ERR(tl, "Error in EDL.\n");
        return;
    }
    MP_TARRAY_APPEND(tl, tl->sources, tl->num_sources, tl->demuxer);
    if (!p->allow_any)
        fix_filenames(parts, tl->demuxer->filename);
    build_timeline(tl, parts);
    talloc_free(parts);
}