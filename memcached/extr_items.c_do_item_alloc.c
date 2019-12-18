#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t const uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ rel_time_t ;
struct TYPE_11__ {unsigned int orig_clsid; TYPE_2__* head; scalar_t__ size; scalar_t__ used; scalar_t__ prev; scalar_t__ next; } ;
typedef  TYPE_1__ item_chunk ;
struct TYPE_12__ {int it_flags; unsigned int slabs_clsid; size_t nkey; int nbytes; scalar_t__ exptime; scalar_t__ h_next; scalar_t__ prev; scalar_t__ next; } ;
typedef  TYPE_2__ item ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_14__ {int /*<<< orphan*/  outofmemory; } ;
struct TYPE_13__ {size_t slab_chunk_size_max; scalar_t__ const temporary_ttl; scalar_t__ use_cas; scalar_t__ lru_segmented; scalar_t__ temp_lru; } ;

/* Variables and functions */
 unsigned int COLD_LRU ; 
 int /*<<< orphan*/  DEBUG_REFCNT (TYPE_2__*,char) ; 
 unsigned int HOT_LRU ; 
 int ITEM_CAS ; 
 int ITEM_CFLAGS ; 
 int ITEM_CHUNKED ; 
 int /*<<< orphan*/  ITEM_key (TYPE_2__*) ; 
 scalar_t__ ITEM_schunk (TYPE_2__*) ; 
 int /*<<< orphan*/  ITEM_suffix (TYPE_2__*) ; 
 unsigned int TEMP_LRU ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ const current_time ; 
 TYPE_2__* do_item_alloc_pull (size_t,unsigned int) ; 
 size_t item_make_header (size_t const,unsigned int const,int const,char*,size_t const*) ; 
 TYPE_4__* itemstats ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ settings ; 
 unsigned int slabs_clsid (int) ; 

item *do_item_alloc(char *key, const size_t nkey, const unsigned int flags,
                    const rel_time_t exptime, const int nbytes) {
    uint8_t nsuffix;
    item *it = NULL;
    char suffix[40];
    // Avoid potential underflows.
    if (nbytes < 2)
        return 0;

    size_t ntotal = item_make_header(nkey + 1, flags, nbytes, suffix, &nsuffix);
    if (settings.use_cas) {
        ntotal += sizeof(uint64_t);
    }

    unsigned int id = slabs_clsid(ntotal);
    unsigned int hdr_id = 0;
    if (id == 0)
        return 0;

    /* This is a large item. Allocate a header object now, lazily allocate
     *  chunks while reading the upload.
     */
    if (ntotal > settings.slab_chunk_size_max) {
        /* We still link this item into the LRU for the larger slab class, but
         * we're pulling a header from an entirely different slab class. The
         * free routines handle large items specifically.
         */
        int htotal = nkey + 1 + nsuffix + sizeof(item) + sizeof(item_chunk);
        if (settings.use_cas) {
            htotal += sizeof(uint64_t);
        }
#ifdef NEED_ALIGN
        // header chunk needs to be padded on some systems
        int remain = htotal % 8;
        if (remain != 0) {
            htotal += 8 - remain;
        }
#endif
        hdr_id = slabs_clsid(htotal);
        it = do_item_alloc_pull(htotal, hdr_id);
        /* setting ITEM_CHUNKED is fine here because we aren't LINKED yet. */
        if (it != NULL)
            it->it_flags |= ITEM_CHUNKED;
    } else {
        it = do_item_alloc_pull(ntotal, id);
    }

    if (it == NULL) {
        pthread_mutex_lock(&lru_locks[id]);
        itemstats[id].outofmemory++;
        pthread_mutex_unlock(&lru_locks[id]);
        return NULL;
    }

    assert(it->it_flags == 0 || it->it_flags == ITEM_CHUNKED);
    //assert(it != heads[id]);

    /* Refcount is seeded to 1 by slabs_alloc() */
    it->next = it->prev = 0;

    /* Items are initially loaded into the HOT_LRU. This is '0' but I want at
     * least a note here. Compiler (hopefully?) optimizes this out.
     */
    if (settings.temp_lru &&
            exptime - current_time <= settings.temporary_ttl) {
        id |= TEMP_LRU;
    } else if (settings.lru_segmented) {
        id |= HOT_LRU;
    } else {
        /* There is only COLD in compat-mode */
        id |= COLD_LRU;
    }
    it->slabs_clsid = id;

    DEBUG_REFCNT(it, '*');
    it->it_flags |= settings.use_cas ? ITEM_CAS : 0;
    it->it_flags |= nsuffix != 0 ? ITEM_CFLAGS : 0;
    it->nkey = nkey;
    it->nbytes = nbytes;
    memcpy(ITEM_key(it), key, nkey);
    it->exptime = exptime;
    if (nsuffix > 0) {
        memcpy(ITEM_suffix(it), &flags, sizeof(flags));
    }

    /* Initialize internal chunk. */
    if (it->it_flags & ITEM_CHUNKED) {
        item_chunk *chunk = (item_chunk *) ITEM_schunk(it);

        chunk->next = 0;
        chunk->prev = 0;
        chunk->used = 0;
        chunk->size = 0;
        chunk->head = it;
        chunk->orig_clsid = hdr_id;
    }
    it->h_next = 0;

    return it;
}