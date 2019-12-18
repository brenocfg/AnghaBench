#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sha1tmp ;
typedef  int /*<<< orphan*/  padtmp ;
typedef  int /*<<< orphan*/  md5tmp ;
struct TYPE_5__ {int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
typedef  TYPE_1__ MD5_SHA1_CTX ;

/* Variables and functions */
 int EVP_CTRL_SSL3_MASTER_SECRET ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  md5_sha1_init (TYPE_1__*) ; 
 scalar_t__ md5_sha1_update (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

int md5_sha1_ctrl(MD5_SHA1_CTX *mctx, int cmd, int mslen, void *ms)
{
    unsigned char padtmp[48];
    unsigned char md5tmp[MD5_DIGEST_LENGTH];
    unsigned char sha1tmp[SHA_DIGEST_LENGTH];

    if (cmd != EVP_CTRL_SSL3_MASTER_SECRET)
        return -2;

    if (mctx == NULL)
        return 0;

    /* SSLv3 client auth handling: see RFC-6101 5.6.8 */
    if (mslen != 48)
        return 0;

    /* At this point hash contains all handshake messages, update
     * with master secret and pad_1.
     */

    if (md5_sha1_update(mctx, ms, mslen) <= 0)
        return 0;

    /* Set padtmp to pad_1 value */
    memset(padtmp, 0x36, sizeof(padtmp));

    if (!MD5_Update(&mctx->md5, padtmp, sizeof(padtmp)))
        return 0;

    if (!MD5_Final(md5tmp, &mctx->md5))
        return 0;

    if (!SHA1_Update(&mctx->sha1, padtmp, 40))
        return 0;

    if (!SHA1_Final(sha1tmp, &mctx->sha1))
        return 0;

    /* Reinitialise context */

    if (!md5_sha1_init(mctx))
        return 0;

    if (md5_sha1_update(mctx, ms, mslen) <= 0)
        return 0;

    /* Set padtmp to pad_2 value */
    memset(padtmp, 0x5c, sizeof(padtmp));

    if (!MD5_Update(&mctx->md5, padtmp, sizeof(padtmp)))
        return 0;

    if (!MD5_Update(&mctx->md5, md5tmp, sizeof(md5tmp)))
        return 0;

    if (!SHA1_Update(&mctx->sha1, padtmp, 40))
        return 0;

    if (!SHA1_Update(&mctx->sha1, sha1tmp, sizeof(sha1tmp)))
        return 0;

    /* Now when ctx is finalised it will return the SSL v3 hash value */

    OPENSSL_cleanse(md5tmp, sizeof(md5tmp));
    OPENSSL_cleanse(sha1tmp, sizeof(sha1tmp));

    return 1;
}