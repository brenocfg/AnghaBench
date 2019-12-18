#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int num; int shutdown; scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__* buf; TYPE_1__* readp; } ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/ * data; int /*<<< orphan*/  max; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ BIO_BUF_MEM ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 141 
#define  BIO_CTRL_EOF 140 
#define  BIO_CTRL_FLUSH 139 
#define  BIO_CTRL_GET_CLOSE 138 
#define  BIO_CTRL_INFO 137 
#define  BIO_CTRL_PENDING 136 
#define  BIO_CTRL_POP 135 
#define  BIO_CTRL_PUSH 134 
#define  BIO_CTRL_RESET 133 
#define  BIO_CTRL_SET_CLOSE 132 
#define  BIO_CTRL_WPENDING 131 
#define  BIO_C_GET_BUF_MEM_PTR 130 
#define  BIO_C_SET_BUF_MEM 129 
#define  BIO_C_SET_BUF_MEM_EOF_RETURN 128 
 int BIO_FLAGS_MEM_RDONLY ; 
 int BIO_FLAGS_NONCLEAR_RST ; 
 int /*<<< orphan*/  mem_buf_free (TYPE_3__*) ; 
 int /*<<< orphan*/  mem_buf_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long mem_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    char **pptr;
    BIO_BUF_MEM *bbm = (BIO_BUF_MEM *)b->ptr;
    BUF_MEM *bm;

    if (b->flags & BIO_FLAGS_MEM_RDONLY)
        bm = bbm->buf;
    else
        bm = bbm->readp;

    switch (cmd) {
    case BIO_CTRL_RESET:
        bm = bbm->buf;
        if (bm->data != NULL) {
            if (!(b->flags & BIO_FLAGS_MEM_RDONLY)) {
                if (!(b->flags & BIO_FLAGS_NONCLEAR_RST)) {
                    memset(bm->data, 0, bm->max);
                    bm->length = 0;
                }
                *bbm->readp = *bbm->buf;
            } else {
                /* For read only case just reset to the start again */
                *bbm->buf = *bbm->readp;
            }
        }
        break;
    case BIO_CTRL_EOF:
        ret = (long)(bm->length == 0);
        break;
    case BIO_C_SET_BUF_MEM_EOF_RETURN:
        b->num = (int)num;
        break;
    case BIO_CTRL_INFO:
        ret = (long)bm->length;
        if (ptr != NULL) {
            pptr = (char **)ptr;
            *pptr = (char *)&(bm->data[0]);
        }
        break;
    case BIO_C_SET_BUF_MEM:
        mem_buf_free(b);
        b->shutdown = (int)num;
        bbm->buf = ptr;
        *bbm->readp = *bbm->buf;
        break;
    case BIO_C_GET_BUF_MEM_PTR:
        if (ptr != NULL) {
            if (!(b->flags & BIO_FLAGS_MEM_RDONLY))
                mem_buf_sync(b);
            bm = bbm->buf;
            pptr = (char **)ptr;
            *pptr = (char *)bm;
        }
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = (long)b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_WPENDING:
        ret = 0L;
        break;
    case BIO_CTRL_PENDING:
        ret = (long)bm->length;
        break;
    case BIO_CTRL_DUP:
    case BIO_CTRL_FLUSH:
        ret = 1;
        break;
    case BIO_CTRL_PUSH:
    case BIO_CTRL_POP:
    default:
        ret = 0;
        break;
    }
    return ret;
}