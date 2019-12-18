#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* buffer; scalar_t__ len; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,scalar_t__) ; 

void rand_pool_reattach(RAND_POOL *pool, unsigned char *buffer)
{
    pool->buffer = buffer;
    OPENSSL_cleanse(pool->buffer, pool->len);
    pool->len = 0;
}