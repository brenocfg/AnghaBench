#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int used; struct TYPE_5__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ item_chunk ;
struct TYPE_6__ {int it_flags; } ;
typedef  TYPE_2__ item ;
typedef  int /*<<< orphan*/  conn ;

/* Variables and functions */
 int ITEM_CHUNKED ; 
 scalar_t__ ITEM_schunk (TYPE_2__*) ; 
 scalar_t__ add_iov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int add_chunked_item_iovs(conn *c, item *it, int len) {
    assert(it->it_flags & ITEM_CHUNKED);
    item_chunk *ch = (item_chunk *) ITEM_schunk(it);
    while (ch) {
        int todo = (len > ch->used) ? ch->used : len;
        if (add_iov(c, ch->data, todo) != 0) {
            return -1;
        }
        ch = ch->next;
        len -= todo;
    }
    return 0;
}