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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int do_pk8pkey_fp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,void*) ; 

int i2d_PKCS8PrivateKey_nid_fp(FILE *fp, const EVP_PKEY *x, int nid,
                               char *kstr, int klen,
                               pem_password_cb *cb, void *u)
{
    return do_pk8pkey_fp(fp, x, 1, nid, NULL, kstr, klen, cb, u);
}