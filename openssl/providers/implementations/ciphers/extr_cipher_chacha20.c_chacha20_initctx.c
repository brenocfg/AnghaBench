#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PROV_CHACHA20_CTX ;

/* Variables and functions */
 int CHACHA20_BLKLEN ; 
 int /*<<< orphan*/  CHACHA20_FLAGS ; 
 int CHACHA20_IVLEN ; 
 int CHACHA20_KEYLEN ; 
 int /*<<< orphan*/  PROV_CIPHER_HW_chacha20 (int) ; 
 int /*<<< orphan*/  cipher_generic_initkey (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void chacha20_initctx(PROV_CHACHA20_CTX *ctx)
{
    cipher_generic_initkey(ctx, CHACHA20_KEYLEN * 8,
                           CHACHA20_BLKLEN * 8,
                           CHACHA20_IVLEN * 8,
                           0, CHACHA20_FLAGS,
                           PROV_CIPHER_HW_chacha20(CHACHA20_KEYLEN * 8),
                           NULL);
}