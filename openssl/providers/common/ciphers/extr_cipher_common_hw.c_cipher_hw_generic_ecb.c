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
struct TYPE_3__ {size_t blocksize; int /*<<< orphan*/  ks; int /*<<< orphan*/  (* block ) (unsigned char const*,unsigned char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,int /*<<< orphan*/ ) ; 

int cipher_hw_generic_ecb(PROV_CIPHER_CTX *dat, unsigned char *out,
                          const unsigned char *in, size_t len)
{
    size_t i, bl = dat->blocksize;

    if (len < bl)
        return 1;

    for (i = 0, len -= bl; i <= len; i += bl)
        (*dat->block) (in + i, out + i, dat->ks);

    return 1;
}