#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  V; int /*<<< orphan*/  C; } ;
struct TYPE_7__ {TYPE_2__ hash; } ;
struct TYPE_9__ {int /*<<< orphan*/  seedlen; TYPE_1__ data; } ;
typedef  TYPE_2__ RAND_DRBG_HASH ;
typedef  TYPE_3__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  hash_df (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int hash_df1 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drbg_hash_reseed(RAND_DRBG *drbg,
                            const unsigned char *ent, size_t ent_len,
                            const unsigned char *adin, size_t adin_len)
{
    RAND_DRBG_HASH *hash = &drbg->data.hash;

    /* (Step 1-2) V = Hash_df(0x01 || V || entropy_input || additional_input)*/
    /* V about to be updated so use C as output instead */
    if (!hash_df(drbg, hash->C, 0x01, hash->V, drbg->seedlen, ent, ent_len,
                 adin, adin_len))
        return 0;
    memcpy(hash->V, hash->C, drbg->seedlen);
    /* (Step 4) C = Hash_df(0x00||V, seedlen) */
    return hash_df1(drbg, hash->C, 0x00, hash->V, drbg->seedlen);
}