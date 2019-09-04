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
struct TYPE_3__ {int (* blocksize ) () ;int block_size; int /*<<< orphan*/ * prov; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 int stub1 () ; 

int EVP_CIPHER_block_size(const EVP_CIPHER *cipher)
{
    if (cipher->prov != NULL) {
        if (cipher->blocksize != NULL)
            return cipher->blocksize();
        /* We default to a block size of 1 */
        return 1;
    }
    return cipher->block_size;
}