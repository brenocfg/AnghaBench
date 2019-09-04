#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ameth; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int ED448_BITS ; 
 scalar_t__ IS25519 (int /*<<< orphan*/ ) ; 
 scalar_t__ ISX448 (int /*<<< orphan*/ ) ; 
 int X25519_BITS ; 
 int X448_BITS ; 

__attribute__((used)) static int ecx_bits(const EVP_PKEY *pkey)
{
    if (IS25519(pkey->ameth->pkey_id)) {
        return X25519_BITS;
    } else if(ISX448(pkey->ameth->pkey_id)) {
        return X448_BITS;
    } else {
        return ED448_BITS;
    }
}