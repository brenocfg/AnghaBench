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
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_F_DSAPARAMS_PRINT_FP ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DSAparams_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 

int DSAparams_print_fp(FILE *fp, const DSA *x)
{
    BIO *b;
    int ret;

    if ((b = BIO_new(BIO_s_file())) == NULL) {
        DSAerr(DSA_F_DSAPARAMS_PRINT_FP, ERR_R_BUF_LIB);
        return 0;
    }
    BIO_set_fp(b, fp, BIO_NOCLOSE);
    ret = DSAparams_print(b, x);
    BIO_free(b);
    return ret;
}