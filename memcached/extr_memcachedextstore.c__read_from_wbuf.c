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
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_6__ {scalar_t__ written; TYPE_3__* wbuf; } ;
typedef  TYPE_1__ store_page ;
struct TYPE_7__ {scalar_t__ offset; int len; int iovcnt; struct iovec* iov; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ obj_io ;
struct TYPE_8__ {scalar_t__ size; unsigned int buf; unsigned int offset; } ;
typedef  TYPE_3__ _store_wbuf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static inline int _read_from_wbuf(store_page *p, obj_io *io) {
    _store_wbuf *wbuf = p->wbuf;
    assert(wbuf != NULL);
    assert(io->offset < p->written + wbuf->size);
    if (io->iov == NULL) {
        memcpy(io->buf, wbuf->buf + (io->offset - wbuf->offset), io->len);
    } else {
        int x;
        unsigned int off = io->offset - wbuf->offset;
        // need to loop fill iovecs
        for (x = 0; x < io->iovcnt; x++) {
            struct iovec *iov = &io->iov[x];
            memcpy(iov->iov_base, wbuf->buf + off, iov->iov_len);
            off += iov->iov_len;
        }
    }
    return io->len;
}