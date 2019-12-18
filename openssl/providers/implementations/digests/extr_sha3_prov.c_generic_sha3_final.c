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
typedef  int /*<<< orphan*/  KECCAK1600_CTX ;

/* Variables and functions */
 int sha3_final (unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generic_sha3_final(unsigned char *md, void *vctx)
{
    return sha3_final(md, (KECCAK1600_CTX *)vctx);
}