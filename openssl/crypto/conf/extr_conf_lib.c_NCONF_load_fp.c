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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONF_F_NCONF_LOAD_FP ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int NCONF_load_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*) ; 

int NCONF_load_fp(CONF *conf, FILE *fp, long *eline)
{
    BIO *btmp;
    int ret;
    if ((btmp = BIO_new_fp(fp, BIO_NOCLOSE)) == NULL) {
        CONFerr(CONF_F_NCONF_LOAD_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = NCONF_load_bio(conf, btmp, eline);
    BIO_free(btmp);
    return ret;
}