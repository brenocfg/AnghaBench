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
struct shash_desc {int dummy; } ;
struct sha1_ctx {scalar_t__ count; scalar_t__ started; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_HASH_INIT ; 
 struct sha1_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int sha1_init(struct shash_desc *desc)
{
    struct sha1_ctx *sctx = shash_desc_ctx(desc);
    
    SHA_HASH_INIT;

    sctx->started = 0;
    sctx->count = 0;
    return 0;
}