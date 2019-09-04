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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  pub_key; } ;
typedef  TYPE_1__ MDH ;

/* Variables and functions */
 scalar_t__ MP_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_setbin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
DHGetPublicKey(MDH *dh, uint8_t *pubkey, size_t nPubkeyLen)
{
    int len;
    if (!dh || !dh->pub_key)
        return 0;

    len = (int)MP_bytes(dh->pub_key);
    if (len <= 0 || len > (int) nPubkeyLen)
        return 0;

    memset(pubkey, 0, nPubkeyLen);
    MP_setbin(dh->pub_key, pubkey + (nPubkeyLen - len), len);
    return 1;
}