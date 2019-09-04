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
struct TYPE_3__ {int /*<<< orphan*/  ks; int /*<<< orphan*/  (* block ) (unsigned char const*,unsigned char*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ PROV_AES_KEY ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aes_ecb_cipher(PROV_AES_KEY *dat, unsigned char *out,
                          const unsigned char *in, size_t len)
{
    size_t i;

    if (len < AES_BLOCK_SIZE)
        return 1;

    for (i = 0, len -= AES_BLOCK_SIZE; i <= len; i += AES_BLOCK_SIZE)
        (*dat->block) (in + i, out + i, &dat->ks);

    return 1;
}