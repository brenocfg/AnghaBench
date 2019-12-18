#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p; TYPE_1__* meth; } ;
struct TYPE_5__ {int (* compute_key ) (unsigned char*,int /*<<< orphan*/  const*,TYPE_2__*) ;} ;
typedef  TYPE_2__ DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (unsigned char*,int /*<<< orphan*/  const*,TYPE_2__*) ; 

int DH_compute_key_padded(unsigned char *key, const BIGNUM *pub_key, DH *dh)
{
    int rv, pad;
    rv = dh->meth->compute_key(key, pub_key, dh);
    if (rv <= 0)
        return rv;
    pad = BN_num_bytes(dh->p) - rv;
    if (pad > 0) {
        memmove(key + pad, key, rv);
        memset(key, 0, pad);
    }
    return rv + pad;
}