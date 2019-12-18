#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* EVP_sha1 () ; 
 int /*<<< orphan*/  RSA_F_RSA_ALGOR_TO_MD ; 
 int /*<<< orphan*/  RSA_R_UNKNOWN_DIGEST ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const EVP_MD *rsa_algor_to_md(X509_ALGOR *alg)
{
    const EVP_MD *md;

    if (!alg)
        return EVP_sha1();
    md = EVP_get_digestbyobj(alg->algorithm);
    if (md == NULL)
        RSAerr(RSA_F_RSA_ALGOR_TO_MD, RSA_R_UNKNOWN_DIGEST);
    return md;
}