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
struct playlist_entry {int /*<<< orphan*/  stream_flags; scalar_t__ filename; } ;
struct MPContext {int /*<<< orphan*/  open_active; TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  prefetch_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,scalar_t__) ; 
 struct playlist_entry* mp_next_file (struct MPContext*,int,int,int) ; 
 int /*<<< orphan*/  start_open (struct MPContext*,scalar_t__,int /*<<< orphan*/ ,int) ; 

void prefetch_next(struct MPContext *mpctx)
{
    if (!mpctx->opts->prefetch_open)
        return;

    struct playlist_entry *new_entry = mp_next_file(mpctx, +1, false, false);
    if (new_entry && !mpctx->open_active && new_entry->filename) {
        MP_VERBOSE(mpctx, "Prefetching: %s\n", new_entry->filename);
        start_open(mpctx, new_entry->filename, new_entry->stream_flags, true);
    }
}