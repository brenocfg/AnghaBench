#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ mc_ptr_t ;
struct TYPE_6__ {TYPE_2__* head; struct TYPE_6__* prev; struct TYPE_6__* next; int /*<<< orphan*/  orig_clsid; } ;
typedef  TYPE_1__ item_chunk ;
struct TYPE_7__ {int it_flags; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_2__ item ;
struct TYPE_8__ {unsigned int slab_page_size; scalar_t__ verbose; } ;

/* Variables and functions */
 int ITEM_CHUNK ; 
 int ITEM_CHUNKED ; 
 int ITEM_LINKED ; 
 scalar_t__ ITEM_schunk (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_item_link_fixup (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int mmap_base ; 
 TYPE_3__ settings ; 
 int slabmem_limit ; 
 int slabs_fixup (char*,int) ; 
 int slabs_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

unsigned int restart_fixup(void *orig_addr) {
    struct timeval tv;
    uint64_t checked = 0;
    const unsigned int page_size = settings.slab_page_size;
    unsigned int page_remain = page_size;

    gettimeofday(&tv, NULL);
    if (settings.verbose > 0) {
        fprintf(stderr, "[restart] original memory base: [%p] new base: [%p]\n", orig_addr, mmap_base);
        fprintf(stderr, "[restart] recovery start [%d.%d]\n", (int)tv.tv_sec, (int)tv.tv_usec);
    }

    // since chunks don't align with pages, we have to also track page size.
    while (checked < slabmem_limit) {
        //fprintf(stderr, "checked: %lu\n", checked);
        item *it = (item *)((char *)mmap_base + checked);

        int size = slabs_fixup((char *)mmap_base + checked,
                checked % settings.slab_page_size);
        //fprintf(stderr, "id: %d, size: %d\n", it->slabs_clsid, size);
        // slabber gobbled an entire page, skip and move on.
        if (size == -1) {
            assert(page_remain % page_size == 0);
            assert(page_remain == page_size);
            checked += page_remain;
            page_remain = page_size;
            continue;
        }

        if (it->it_flags & ITEM_LINKED) {
            // fixup next/prev links while on LRU.
            if (it->next) {
                it->next = (item *)((mc_ptr_t)it->next - (mc_ptr_t)orig_addr);
                it->next = (item *)((mc_ptr_t)it->next + (mc_ptr_t)mmap_base);
            }
            if (it->prev) {
                it->prev = (item *)((mc_ptr_t)it->prev - (mc_ptr_t)orig_addr);
                it->prev = (item *)((mc_ptr_t)it->prev + (mc_ptr_t)mmap_base);
            }

            //fprintf(stderr, "item was linked\n");
            do_item_link_fixup(it);
        }

        if (it->it_flags & (ITEM_CHUNKED|ITEM_CHUNK)) {
            item_chunk *ch;
            if (it->it_flags & ITEM_CHUNKED) {
                ch = (item_chunk *) ITEM_schunk(it);
                // Sigh. Chunked items are a hack; the clsid is the clsid of
                // the full object (always the largest slab class) rather than
                // the actual chunk.
                // I bet this is fixable :(
                size = slabs_size(ch->orig_clsid);
                //fprintf(stderr, "fixing chunked item header [%d]\n", size);
            } else {
                //fprintf(stderr, "fixing item chunk [%d]\n", size);
                ch = (item_chunk *) it;
            }
            if (ch->next) {
                ch->next = (item_chunk *)((mc_ptr_t)ch->next - (mc_ptr_t)orig_addr);
                ch->next = (item_chunk *)((mc_ptr_t)ch->next + (mc_ptr_t)mmap_base);
            }
            if (ch->prev) {
                ch->prev = (item_chunk *)((mc_ptr_t)ch->prev - (mc_ptr_t)orig_addr);
                ch->prev = (item_chunk *)((mc_ptr_t)ch->prev + (mc_ptr_t)mmap_base);
            }
            if (ch->head) {
                ch->head = (item *)((mc_ptr_t)ch->head - (mc_ptr_t)orig_addr);
                ch->head = (item *)((mc_ptr_t)ch->head + (mc_ptr_t)mmap_base);
            }
        }

        // next chunk
        checked += size;
        page_remain -= size;
        if (size > page_remain) {
            //fprintf(stderr, "doot %d\n", page_remain);
            checked += page_remain;
            page_remain = settings.slab_page_size;
        }
        //assert(checked != 3145728);
    }

    if (settings.verbose > 0) {
        gettimeofday(&tv, NULL);
        fprintf(stderr, "[restart] recovery end [%d.%d]\n", (int)tv.tv_sec, (int)tv.tv_usec);
    }

    return 0;
}