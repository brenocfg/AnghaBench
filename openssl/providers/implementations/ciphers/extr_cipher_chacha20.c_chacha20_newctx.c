#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void PROV_CHACHA20_CTX ;

/* Variables and functions */
 void* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  chacha20_initctx (void*) ; 

__attribute__((used)) static void *chacha20_newctx(void *provctx)
{
     PROV_CHACHA20_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));

     if (ctx != NULL)
         chacha20_initctx(ctx);
     return ctx;
}