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
struct TYPE_4__ {int /*<<< orphan*/  alloc_len; int /*<<< orphan*/  buffer; scalar_t__ secure; int /*<<< orphan*/  attached; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rand_pool_free(RAND_POOL *pool)
{
    if (pool == NULL)
        return;

    /*
     * Although it would be advisable from a cryptographical viewpoint,
     * we are not allowed to clear attached buffers, since they are passed
     * to rand_pool_attach() as `const unsigned char*`.
     * (see corresponding comment in rand_pool_attach()).
     */
    if (!pool->attached) {
        if (pool->secure)
            OPENSSL_secure_clear_free(pool->buffer, pool->alloc_len);
        else
            OPENSSL_clear_free(pool->buffer, pool->alloc_len);
    }

    OPENSSL_free(pool);
}