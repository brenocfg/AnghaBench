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
struct TYPE_7__ {int init; char* ptr; scalar_t__ flags; } ;
struct TYPE_6__ {struct TYPE_6__* ibuf; int /*<<< orphan*/ * obuf; void* obuf_size; void* ibuf_size; } ;
typedef  TYPE_1__ BIO_F_BUFFER_CTX ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 void* DEFAULT_BUFFER_SIZE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 void* OPENSSL_malloc (void*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int buffer_new(BIO *bi)
{
    BIO_F_BUFFER_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));

    if (ctx == NULL)
        return 0;
    ctx->ibuf_size = DEFAULT_BUFFER_SIZE;
    ctx->ibuf = OPENSSL_malloc(DEFAULT_BUFFER_SIZE);
    if (ctx->ibuf == NULL) {
        OPENSSL_free(ctx);
        return 0;
    }
    ctx->obuf_size = DEFAULT_BUFFER_SIZE;
    ctx->obuf = OPENSSL_malloc(DEFAULT_BUFFER_SIZE);
    if (ctx->obuf == NULL) {
        OPENSSL_free(ctx->ibuf);
        OPENSSL_free(ctx);
        return 0;
    }

    bi->init = 1;
    bi->ptr = (char *)ctx;
    bi->flags = 0;
    return 1;
}