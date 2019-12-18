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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/ * MP_t ;
typedef  TYPE_1__ MDH ;

/* Variables and functions */
 size_t INT_MAX ; 
 int MDH_compute_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  MP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_getbin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  MP_gethex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  Q1024 ; 
 int /*<<< orphan*/  assert (size_t) ; 
 scalar_t__ isValidPublicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DHComputeSharedSecretKey(MDH *dh, uint8_t *pubkey, size_t nPubkeyLen,
                         uint8_t *secret)
{
    MP_t q1 = NULL, pubkeyBn = NULL;
    size_t len;
    int res;

    if (!dh || !secret || nPubkeyLen >= INT_MAX)
        return -1;

    MP_getbin(pubkeyBn, pubkey, nPubkeyLen);
    if (!pubkeyBn)
        return -1;

    MP_gethex(q1, Q1024, len);
    assert(len);

    if (isValidPublicKey(pubkeyBn, dh->p, q1))
        res = MDH_compute_key(secret, nPubkeyLen, pubkeyBn, dh);
    else
        res = -1;

    MP_free(q1);
    MP_free(pubkeyBn);

    return res;
}