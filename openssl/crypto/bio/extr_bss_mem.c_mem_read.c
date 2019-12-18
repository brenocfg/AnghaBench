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
struct TYPE_9__ {int flags; int num; scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__* buf; TYPE_1__* readp; } ;
struct TYPE_7__ {size_t length; int data; int max; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ BIO_BUF_MEM ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_3__*) ; 
 int /*<<< orphan*/  BIO_set_retry_read (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 

__attribute__((used)) static int mem_read(BIO *b, char *out, int outl)
{
    int ret = -1;
    BIO_BUF_MEM *bbm = (BIO_BUF_MEM *)b->ptr;
    BUF_MEM *bm = bbm->readp;

    if (b->flags & BIO_FLAGS_MEM_RDONLY)
        bm = bbm->buf;
    BIO_clear_retry_flags(b);
    ret = (outl >= 0 && (size_t)outl > bm->length) ? (int)bm->length : outl;
    if ((out != NULL) && (ret > 0)) {
        memcpy(out, bm->data, ret);
        bm->length -= ret;
        bm->max -= ret;
        bm->data += ret;
    } else if (bm->length == 0) {
        ret = b->num;
        if (ret != 0)
            BIO_set_retry_read(b);
    }
    return ret;
}