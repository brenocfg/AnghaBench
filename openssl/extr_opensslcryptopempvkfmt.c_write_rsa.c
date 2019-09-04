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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int RSA_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_get0_crt_params (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lebn (unsigned char**,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void write_rsa(unsigned char **out, RSA *rsa, int ispub)
{
    int nbyte, hnbyte;
    const BIGNUM *n, *d, *e, *p, *q, *iqmp, *dmp1, *dmq1;

    nbyte = RSA_size(rsa);
    hnbyte = (RSA_bits(rsa) + 15) >> 4;
    RSA_get0_key(rsa, &n, &e, &d);
    write_lebn(out, e, 4);
    write_lebn(out, n, nbyte);
    if (ispub)
        return;
    RSA_get0_factors(rsa, &p, &q);
    RSA_get0_crt_params(rsa, &dmp1, &dmq1, &iqmp);
    write_lebn(out, p, hnbyte);
    write_lebn(out, q, hnbyte);
    write_lebn(out, dmp1, hnbyte);
    write_lebn(out, dmq1, hnbyte);
    write_lebn(out, iqmp, hnbyte);
    write_lebn(out, d, nbyte);
}