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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * digest_md5 () ; 
 int /*<<< orphan*/ * digest_sha1 () ; 
 int /*<<< orphan*/ * digest_sha256 () ; 
 int /*<<< orphan*/ * digest_sha384 () ; 
 int /*<<< orphan*/ * digest_sha512 () ; 

__attribute__((used)) static int ossltest_digest_nids(const int **nids)
{
    static int digest_nids[6] = { 0, 0, 0, 0, 0, 0 };
    static int pos = 0;
    static int init = 0;

    if (!init) {
        const EVP_MD *md;
        if ((md = digest_md5()) != NULL)
            digest_nids[pos++] = EVP_MD_type(md);
        if ((md = digest_sha1()) != NULL)
            digest_nids[pos++] = EVP_MD_type(md);
        if ((md = digest_sha256()) != NULL)
            digest_nids[pos++] = EVP_MD_type(md);
        if ((md = digest_sha384()) != NULL)
            digest_nids[pos++] = EVP_MD_type(md);
        if ((md = digest_sha512()) != NULL)
            digest_nids[pos++] = EVP_MD_type(md);
        digest_nids[pos] = 0;
        init = 1;
    }
    *nids = digest_nids;
    return pos;
}