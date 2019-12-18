#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; TYPE_4__* wbuf; } ;
typedef  TYPE_1__ store_page ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; TYPE_3__* io_stack; } ;
typedef  TYPE_2__ store_engine ;
struct TYPE_11__ {int /*<<< orphan*/  cb; scalar_t__ buf; scalar_t__ len; int /*<<< orphan*/  offset; TYPE_4__* data; int /*<<< orphan*/  page_id; int /*<<< orphan*/  mode; struct TYPE_11__* next; } ;
typedef  TYPE_3__ obj_io ;
struct TYPE_12__ {scalar_t__ buf; scalar_t__ size; int /*<<< orphan*/  offset; scalar_t__ free; } ;
typedef  TYPE_4__ _store_wbuf ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_IO_WRITE ; 
 int /*<<< orphan*/  _wbuf_cb ; 
 int /*<<< orphan*/  extstore_submit (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _submit_wbuf(store_engine *e, store_page *p) {
    _store_wbuf *w;
    pthread_mutex_lock(&e->mutex);
    obj_io *io = e->io_stack;
    e->io_stack = io->next;
    pthread_mutex_unlock(&e->mutex);
    w = p->wbuf;

    // zero out the end of the wbuf to allow blind readback of data.
    memset(w->buf + (w->size - w->free), 0, w->free);

    io->next = NULL;
    io->mode = OBJ_IO_WRITE;
    io->page_id = p->id;
    io->data = w;
    io->offset = w->offset;
    io->len = w->size;
    io->buf = w->buf;
    io->cb = _wbuf_cb;

    extstore_submit(e, io);
}