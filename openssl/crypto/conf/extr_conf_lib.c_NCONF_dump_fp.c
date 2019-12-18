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
 int /*<<< orphan*/  CONF_F_NCONF_DUMP_FP ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int NCONF_dump_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int NCONF_dump_fp(const CONF *conf, FILE *out)
{
    BIO *btmp;
    int ret;
    if ((btmp = BIO_new_fp(out, BIO_NOCLOSE)) == NULL) {
        CONFerr(CONF_F_NCONF_DUMP_FP, ERR_R_BUF_LIB);
        return 0;
    }
    ret = NCONF_dump_bio(conf, btmp);
    BIO_free(btmp);
    return ret;
}