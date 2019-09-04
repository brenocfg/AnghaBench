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
struct md5_sha1_ctx {int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 struct md5_sha1_ctx* EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int final(EVP_MD_CTX *ctx, unsigned char *md)
{
    struct md5_sha1_ctx *mctx = EVP_MD_CTX_md_data(ctx);
    if (!MD5_Final(md, &mctx->md5))
        return 0;
    return SHA1_Final(md + MD5_DIGEST_LENGTH, &mctx->sha1);
}