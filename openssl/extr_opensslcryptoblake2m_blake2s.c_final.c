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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int BLAKE2s_Final (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int final(EVP_MD_CTX *ctx, unsigned char *md)
{
    return BLAKE2s_Final(md, EVP_MD_CTX_md_data(ctx));
}