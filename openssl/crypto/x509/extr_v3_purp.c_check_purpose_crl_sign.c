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
typedef  int /*<<< orphan*/  X509_PURPOSE ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  KU_CRL_SIGN ; 
 int check_ca (int /*<<< orphan*/  const*) ; 
 scalar_t__ ku_reject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_purpose_crl_sign(const X509_PURPOSE *xp, const X509 *x,
                                  int ca)
{
    if (ca) {
        int ca_ret;
        if ((ca_ret = check_ca(x)) != 2)
            return ca_ret;
        else
            return 0;
    }
    if (ku_reject(x, KU_CRL_SIGN))
        return 0;
    return 1;
}