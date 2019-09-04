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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  PEM_F_PEM_READ ; 
 int PEM_read_bio (int /*<<< orphan*/ *,char**,char**,unsigned char**,long*) ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PEM_read(FILE *fp, char **name, char **header, unsigned char **data,
             long *len)
{
    BIO *b;
    int ret;

    if ((b = BIO_new(BIO_s_file())) == NULL) {
        PEMerr(PEM_F_PEM_READ, ERR_R_BUF_LIB);
        return 0;
    }
    BIO_set_fp(b, fp, BIO_NOCLOSE);
    ret = PEM_read_bio(b, name, header, data, len);
    BIO_free(b);
    return ret;
}