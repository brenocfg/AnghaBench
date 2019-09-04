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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int X509_NAME_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 unsigned long XN_FLAG_COMPAT ; 
 int do_name_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,unsigned long) ; 
 int /*<<< orphan*/  send_fp_chars ; 

int X509_NAME_print_ex_fp(FILE *fp, const X509_NAME *nm, int indent,
                          unsigned long flags)
{
    if (flags == XN_FLAG_COMPAT) {
        BIO *btmp;
        int ret;
        btmp = BIO_new_fp(fp, BIO_NOCLOSE);
        if (!btmp)
            return -1;
        ret = X509_NAME_print(btmp, nm, indent);
        BIO_free(btmp);
        return ret;
    }
    return do_name_ex(send_fp_chars, fp, nm, indent, flags);
}