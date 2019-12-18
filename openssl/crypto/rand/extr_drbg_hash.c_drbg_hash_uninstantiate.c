#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  md; } ;
struct TYPE_5__ {TYPE_4__ hash; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_4__*,int) ; 

__attribute__((used)) static int drbg_hash_uninstantiate(RAND_DRBG *drbg)
{
    EVP_MD_free(drbg->data.hash.md);
    EVP_MD_CTX_free(drbg->data.hash.ctx);
    OPENSSL_cleanse(&drbg->data.hash, sizeof(drbg->data.hash));
    return 1;
}