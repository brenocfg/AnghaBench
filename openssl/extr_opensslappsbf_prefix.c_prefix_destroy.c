#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* prefix; } ;
typedef  TYPE_1__ PREFIX_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static int prefix_destroy(BIO *b)
{
    PREFIX_CTX *ctx = BIO_get_data(b);

    OPENSSL_free(ctx->prefix);
    OPENSSL_free(ctx);
    return 1;
}