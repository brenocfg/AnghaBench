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
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_F_CMS_FINAL ; 
 int /*<<< orphan*/  CMS_R_CMS_DATAFINAL_ERROR ; 
 int /*<<< orphan*/  CMS_R_CMS_LIB ; 
 int /*<<< orphan*/  CMS_dataFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMS_dataInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMIME_crlf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  do_free_upto (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CMS_final(CMS_ContentInfo *cms, BIO *data, BIO *dcont, unsigned int flags)
{
    BIO *cmsbio;
    int ret = 0;

    if ((cmsbio = CMS_dataInit(cms, dcont)) == NULL) {
        CMSerr(CMS_F_CMS_FINAL, CMS_R_CMS_LIB);
        return 0;
    }

    SMIME_crlf_copy(data, cmsbio, flags);

    (void)BIO_flush(cmsbio);

    if (!CMS_dataFinal(cms, cmsbio)) {
        CMSerr(CMS_F_CMS_FINAL, CMS_R_CMS_DATAFINAL_ERROR);
        goto err;
    }

    ret = 1;

 err:
    do_free_upto(cmsbio, dcont);

    return ret;

}