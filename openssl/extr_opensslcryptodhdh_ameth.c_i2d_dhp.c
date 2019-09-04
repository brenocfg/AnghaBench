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
struct TYPE_3__ {int /*<<< orphan*/ * ameth; } ;
typedef  TYPE_1__ EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  dhx_asn1_meth ; 
 int i2d_DHparams (int /*<<< orphan*/  const*,unsigned char**) ; 
 int i2d_DHxparams (int /*<<< orphan*/  const*,unsigned char**) ; 

__attribute__((used)) static int i2d_dhp(const EVP_PKEY *pkey, const DH *a, unsigned char **pp)
{
    if (pkey->ameth == &dhx_asn1_meth)
        return i2d_DHxparams(a, pp);
    return i2d_DHparams(a, pp);
}