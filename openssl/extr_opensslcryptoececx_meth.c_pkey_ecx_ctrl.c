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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int EVP_PKEY_CTRL_PEER_KEY ; 

__attribute__((used)) static int pkey_ecx_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    /* Only need to handle peer key for derivation */
    if (type == EVP_PKEY_CTRL_PEER_KEY)
        return 1;
    return -2;
}