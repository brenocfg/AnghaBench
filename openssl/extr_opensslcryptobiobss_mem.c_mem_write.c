#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; scalar_t__ data; } ;
struct TYPE_8__ {int flags; scalar_t__ ptr; } ;
struct TYPE_7__ {TYPE_5__* buf; TYPE_5__* readp; } ;
typedef  TYPE_1__ BIO_BUF_MEM ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_F_MEM_WRITE ; 
 int /*<<< orphan*/  BIO_R_NULL_PARAMETER ; 
 int /*<<< orphan*/  BIO_R_WRITE_TO_READ_ONLY_BIO ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BUF_MEM_grow_clean (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mem_buf_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 

__attribute__((used)) static int mem_write(BIO *b, const char *in, int inl)
{
    int ret = -1;
    int blen;
    BIO_BUF_MEM *bbm = (BIO_BUF_MEM *)b->ptr;

    if (in == NULL) {
        BIOerr(BIO_F_MEM_WRITE, BIO_R_NULL_PARAMETER);
        goto end;
    }
    if (b->flags & BIO_FLAGS_MEM_RDONLY) {
        BIOerr(BIO_F_MEM_WRITE, BIO_R_WRITE_TO_READ_ONLY_BIO);
        goto end;
    }
    BIO_clear_retry_flags(b);
    if (inl == 0)
        return 0;
    blen = bbm->readp->length;
    mem_buf_sync(b);
    if (BUF_MEM_grow_clean(bbm->buf, blen + inl) == 0)
        goto end;
    memcpy(bbm->buf->data + blen, in, inl);
    *bbm->readp = *bbm->buf;
    ret = inl;
 end:
    return ret;
}