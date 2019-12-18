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
struct shash_desc {int dummy; } ;
struct md5_ctx {scalar_t__ started; scalar_t__ byte_count; } ;
struct TYPE_2__ {int SM; int ALGO; int INIT; scalar_t__ ENDI; } ;
struct deu_hash_t {TYPE_1__ controlr; } ;

/* Variables and functions */
 scalar_t__ HASH_START ; 
 struct md5_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int md5_init(struct shash_desc *desc)
{
    struct md5_ctx *mctx = shash_desc_ctx(desc);
    volatile struct deu_hash_t *hash = (struct deu_hash_t *) HASH_START;

    hash->controlr.ENDI = 0;
    hash->controlr.SM = 1;
    hash->controlr.ALGO = 1;    // 1 = md5  0 = sha1
    hash->controlr.INIT = 1;    // Initialize the hash operation by writing a '1' to the INIT bit.

    mctx->byte_count = 0;
    mctx->started = 0;
    return 0;
}