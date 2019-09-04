#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * callback_ex; int /*<<< orphan*/ * callback; int /*<<< orphan*/  num_read; TYPE_1__* method; int /*<<< orphan*/  init; } ;
struct TYPE_6__ {int (* bread ) (TYPE_2__*,void*,size_t,size_t*) ;} ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int BIO_CB_READ ; 
 int BIO_CB_RETURN ; 
 int /*<<< orphan*/  BIO_F_BIO_READ_INTERN ; 
 int /*<<< orphan*/  BIO_R_UNINITIALIZED ; 
 int /*<<< orphan*/  BIO_R_UNSUPPORTED_METHOD ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ bio_call_callback (TYPE_2__*,int,void*,size_t,int /*<<< orphan*/ ,long,int,size_t*) ; 
 int stub1 (TYPE_2__*,void*,size_t,size_t*) ; 

__attribute__((used)) static int bio_read_intern(BIO *b, void *data, size_t dlen, size_t *readbytes)
{
    int ret;

    if ((b == NULL) || (b->method == NULL) || (b->method->bread == NULL)) {
        BIOerr(BIO_F_BIO_READ_INTERN, BIO_R_UNSUPPORTED_METHOD);
        return -2;
    }

    if ((b->callback != NULL || b->callback_ex != NULL) &&
        ((ret = (int)bio_call_callback(b, BIO_CB_READ, data, dlen, 0, 0L, 1L,
                                       NULL)) <= 0))
        return ret;

    if (!b->init) {
        BIOerr(BIO_F_BIO_READ_INTERN, BIO_R_UNINITIALIZED);
        return -2;
    }

    ret = b->method->bread(b, data, dlen, readbytes);

    if (ret > 0)
        b->num_read += (uint64_t)*readbytes;

    if (b->callback != NULL || b->callback_ex != NULL)
        ret = (int)bio_call_callback(b, BIO_CB_READ | BIO_CB_RETURN, data,
                                     dlen, 0, 0L, ret, readbytes);

    /* Shouldn't happen */
    if (ret > 0 && *readbytes > dlen) {
        BIOerr(BIO_F_BIO_READ_INTERN, ERR_R_INTERNAL_ERROR);
        return -1;
    }

    return ret;
}