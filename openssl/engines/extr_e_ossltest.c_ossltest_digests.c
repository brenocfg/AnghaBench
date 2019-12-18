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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
#define  NID_md5 132 
#define  NID_sha1 131 
#define  NID_sha256 130 
#define  NID_sha384 129 
#define  NID_sha512 128 
 int /*<<< orphan*/ * digest_md5 () ; 
 int /*<<< orphan*/ * digest_sha1 () ; 
 int /*<<< orphan*/ * digest_sha256 () ; 
 int /*<<< orphan*/ * digest_sha384 () ; 
 int /*<<< orphan*/ * digest_sha512 () ; 
 int ossltest_digest_nids (int const**) ; 

__attribute__((used)) static int ossltest_digests(ENGINE *e, const EVP_MD **digest,
                          const int **nids, int nid)
{
    int ok = 1;
    if (!digest) {
        /* We are returning a list of supported nids */
        return ossltest_digest_nids(nids);
    }
    /* We are being asked for a specific digest */
    switch (nid) {
    case NID_md5:
        *digest = digest_md5();
        break;
    case NID_sha1:
        *digest = digest_sha1();
        break;
    case NID_sha256:
        *digest = digest_sha256();
        break;
    case NID_sha384:
        *digest = digest_sha384();
        break;
    case NID_sha512:
        *digest = digest_sha512();
        break;
    default:
        ok = 0;
        *digest = NULL;
        break;
    }
    return ok;
}