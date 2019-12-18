#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {scalar_t__ exptime; scalar_t__ time; int it_flags; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_2__ item ;
struct TYPE_12__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  cbuf; } ;
struct TYPE_14__ {TYPE_1__ c; } ;
typedef  TYPE_3__ crawler_module_t ;

/* Variables and functions */
 int ITEM_FETCHED ; 
 int /*<<< orphan*/  ITEM_clsid (TYPE_2__*) ; 
 scalar_t__ ITEM_get_cas (TYPE_2__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_2__*) ; 
 scalar_t__ ITEM_ntotal (TYPE_2__*) ; 
 int KEY_MAX_URI_ENCODED_LENGTH ; 
 int LRU_CRAWLER_WRITEBUF ; 
 int /*<<< orphan*/  bipbuf_push (int /*<<< orphan*/ ,int) ; 
 scalar_t__ current_time ; 
 int item_is_flushed (TYPE_2__*) ; 
 scalar_t__ process_started ; 
 int /*<<< orphan*/  refcount_decr (TYPE_2__*) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,char*,int,unsigned long long,unsigned long long,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uriencode (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void crawler_metadump_eval(crawler_module_t *cm, item *it, uint32_t hv, int i) {
    //int slab_id = CLEAR_LRU(i);
    char keybuf[KEY_MAX_URI_ENCODED_LENGTH];
    int is_flushed = item_is_flushed(it);
    /* Ignore expired content. */
    if ((it->exptime != 0 && it->exptime < current_time)
        || is_flushed) {
        refcount_decr(it);
        return;
    }
    // TODO: uriencode directly into the buffer.
    uriencode(ITEM_key(it), keybuf, it->nkey, KEY_MAX_URI_ENCODED_LENGTH);
    int total = snprintf(cm->c.cbuf, 4096,
            "key=%s exp=%ld la=%llu cas=%llu fetch=%s cls=%u size=%lu\n",
            keybuf,
            (it->exptime == 0) ? -1 : (long)(it->exptime + process_started),
            (unsigned long long)(it->time + process_started),
            (unsigned long long)ITEM_get_cas(it),
            (it->it_flags & ITEM_FETCHED) ? "yes" : "no",
            ITEM_clsid(it),
            (unsigned long) ITEM_ntotal(it));
    refcount_decr(it);
    // TODO: some way of tracking the errors. these are very unlikely though.
    if (total >= LRU_CRAWLER_WRITEBUF - 1 || total <= 0) {
        /* Failed to write, don't push it. */
        return;
    }
    bipbuf_push(cm->c.buf, total);
}