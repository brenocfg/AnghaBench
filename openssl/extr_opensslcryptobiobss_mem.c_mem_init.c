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
struct TYPE_6__ {int shutdown; int init; int num; char* ptr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/ * readp; } ;
typedef  TYPE_1__ BIO_BUF_MEM ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUF_MEM_new_ex (unsigned long) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 void* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int mem_init(BIO *bi, unsigned long flags)
{
    BIO_BUF_MEM *bb = OPENSSL_zalloc(sizeof(*bb));

    if (bb == NULL)
        return 0;
    if ((bb->buf = BUF_MEM_new_ex(flags)) == NULL) {
        OPENSSL_free(bb);
        return 0;
    }
    if ((bb->readp = OPENSSL_zalloc(sizeof(*bb->readp))) == NULL) {
        BUF_MEM_free(bb->buf);
        OPENSSL_free(bb);
        return 0;
    }
    *bb->readp = *bb->buf;
    bi->shutdown = 1;
    bi->init = 1;
    bi->num = -1;
    bi->ptr = (char *)bb;
    return 1;
}