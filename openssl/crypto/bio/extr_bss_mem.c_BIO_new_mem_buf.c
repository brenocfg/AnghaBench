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
struct TYPE_8__ {scalar_t__ num; int /*<<< orphan*/  flags; scalar_t__ ptr; } ;
struct TYPE_7__ {TYPE_1__* buf; TYPE_1__* readp; } ;
struct TYPE_6__ {size_t length; size_t max; void* data; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ BIO_BUF_MEM ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_F_BIO_NEW_MEM_BUF ; 
 int /*<<< orphan*/  BIO_R_NULL_PARAMETER ; 
 TYPE_3__* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (void const*) ; 

BIO *BIO_new_mem_buf(const void *buf, int len)
{
    BIO *ret;
    BUF_MEM *b;
    BIO_BUF_MEM *bb;
    size_t sz;

    if (buf == NULL) {
        BIOerr(BIO_F_BIO_NEW_MEM_BUF, BIO_R_NULL_PARAMETER);
        return NULL;
    }
    sz = (len < 0) ? strlen(buf) : (size_t)len;
    if ((ret = BIO_new(BIO_s_mem())) == NULL)
        return NULL;
    bb = (BIO_BUF_MEM *)ret->ptr;
    b = bb->buf;
    /* Cast away const and trust in the MEM_RDONLY flag. */
    b->data = (void *)buf;
    b->length = sz;
    b->max = sz;
    *bb->readp = *bb->buf;
    ret->flags |= BIO_FLAGS_MEM_RDONLY;
    /* Since this is static data retrying won't help */
    ret->num = 0;
    return ret;
}