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
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_F_CMS_DATA ; 
 int /*<<< orphan*/  CMS_R_TYPE_NOT_DATA ; 
 int /*<<< orphan*/ * CMS_dataInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_get0_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NID_pkcs7_data ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int cms_copy_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

int CMS_data(CMS_ContentInfo *cms, BIO *out, unsigned int flags)
{
    BIO *cont;
    int r;
    if (OBJ_obj2nid(CMS_get0_type(cms)) != NID_pkcs7_data) {
        CMSerr(CMS_F_CMS_DATA, CMS_R_TYPE_NOT_DATA);
        return 0;
    }
    cont = CMS_dataInit(cms, NULL);
    if (!cont)
        return 0;
    r = cms_copy_content(out, cont, flags);
    BIO_free_all(cont);
    return r;
}