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
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_ContentInfo_free (int /*<<< orphan*/ *) ; 
 unsigned int CMS_DETACHED ; 
 unsigned int CMS_STREAM ; 
 scalar_t__ CMS_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  CMS_set_detached (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * cms_DigestedData_create (int /*<<< orphan*/  const*) ; 

CMS_ContentInfo *CMS_digest_create(BIO *in, const EVP_MD *md,
                                   unsigned int flags)
{
    CMS_ContentInfo *cms;
    if (!md)
        md = EVP_sha1();
    cms = cms_DigestedData_create(md);
    if (!cms)
        return NULL;

    if (!(flags & CMS_DETACHED))
        CMS_set_detached(cms, 0);

    if ((flags & CMS_STREAM) || CMS_final(cms, in, NULL, flags))
        return cms;

    CMS_ContentInfo_free(cms);
    return NULL;
}