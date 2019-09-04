#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* free_func ) (void*) ;} ;
typedef  TYPE_1__ OPENSSL_CTX_METHOD ;
typedef  int /*<<< orphan*/  CRYPTO_EX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void openssl_ctx_generic_free(void *parent_ign, void *ptr,
                                     CRYPTO_EX_DATA *ad, int index,
                                     long argl_ign, void *argp)
{
    const OPENSSL_CTX_METHOD *meth = argp;

    meth->free_func(ptr);
}