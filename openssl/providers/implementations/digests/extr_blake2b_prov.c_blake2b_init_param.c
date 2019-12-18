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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ * h; int /*<<< orphan*/  outlen; } ;
struct TYPE_6__ {int /*<<< orphan*/  digest_length; } ;
typedef  TYPE_1__ BLAKE2B_PARAM ;
typedef  TYPE_2__ BLAKE2B_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blake2b_init0 (TYPE_2__*) ; 
 int /*<<< orphan*/  load64 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void blake2b_init_param(BLAKE2B_CTX *S, const BLAKE2B_PARAM *P)
{
    size_t i;
    const uint8_t *p = (const uint8_t *)(P);

    blake2b_init0(S);
    S->outlen = P->digest_length;

    /* The param struct is carefully hand packed, and should be 64 bytes on
     * every platform. */
    assert(sizeof(BLAKE2B_PARAM) == 64);
    /* IV XOR ParamBlock */
    for (i = 0; i < 8; ++i) {
        S->h[i] ^= load64(p + sizeof(S->h[i]) * i);
    }
}