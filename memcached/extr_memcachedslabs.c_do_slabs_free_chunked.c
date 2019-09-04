#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int requested; int /*<<< orphan*/  sl_curr; TYPE_2__* slots; } ;
typedef  TYPE_1__ slabclass_t ;
struct TYPE_9__ {scalar_t__ it_flags; size_t slabs_clsid; size_t orig_clsid; scalar_t__ size; struct TYPE_9__* prev; struct TYPE_9__* next; scalar_t__ nsuffix; scalar_t__ nkey; } ;
typedef  TYPE_2__ item_chunk ;
typedef  TYPE_2__ item ;
struct TYPE_10__ {scalar_t__ use_cas; } ;

/* Variables and functions */
 scalar_t__ ITEM_CHUNK ; 
 void* ITEM_SLABBED ; 
 scalar_t__ ITEM_schunk (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__ settings ; 
 TYPE_1__* slabclass ; 

__attribute__((used)) static void do_slabs_free_chunked(item *it, const size_t size) {
    item_chunk *chunk = (item_chunk *) ITEM_schunk(it);
    slabclass_t *p;

    it->it_flags = ITEM_SLABBED;
    it->slabs_clsid = 0;
    it->prev = 0;
    // header object's original classid is stored in chunk.
    p = &slabclass[chunk->orig_clsid];
    if (chunk->next) {
        chunk = chunk->next;
        chunk->prev = 0;
    } else {
        // header with no attached chunk
        chunk = NULL;
    }

    // return the header object.
    // TODO: This is in three places, here and in do_slabs_free().
    it->prev = 0;
    it->next = p->slots;
    if (it->next) it->next->prev = it;
    p->slots = it;
    p->sl_curr++;
    // TODO: macro
#ifdef NEED_ALIGN
    int total = it->nkey + 1 + it->nsuffix + sizeof(item) + sizeof(item_chunk);
    if (total % 8 != 0) {
        total += 8 - (total % 8);
    }
    p->requested -= total;
#else
    p->requested -= it->nkey + 1 + it->nsuffix + sizeof(item) + sizeof(item_chunk);
#endif
    if (settings.use_cas) {
        p->requested -= sizeof(uint64_t);
    }

    item_chunk *next_chunk;
    while (chunk) {
        assert(chunk->it_flags == ITEM_CHUNK);
        chunk->it_flags = ITEM_SLABBED;
        p = &slabclass[chunk->slabs_clsid];
        chunk->slabs_clsid = 0;
        next_chunk = chunk->next;

        chunk->prev = 0;
        chunk->next = p->slots;
        if (chunk->next) chunk->next->prev = chunk;
        p->slots = chunk;
        p->sl_curr++;
        p->requested -= chunk->size + sizeof(item_chunk);

        chunk = next_chunk;
    }

    return;
}