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
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_3__ {int /*<<< orphan*/ * pss; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RSA_F_RSA_PARAM_DECODE ; 
 int /*<<< orphan*/  RSA_R_INVALID_PSS_PARAMETERS ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V_ASN1_SEQUENCE ; 
 int V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int*,void const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * rsa_pss_decode (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int rsa_param_decode(RSA *rsa, const X509_ALGOR *alg)
{
    const ASN1_OBJECT *algoid;
    const void *algp;
    int algptype;

    X509_ALGOR_get0(&algoid, &algptype, &algp, alg);
    if (OBJ_obj2nid(algoid) != EVP_PKEY_RSA_PSS)
        return 1;
    if (algptype == V_ASN1_UNDEF)
        return 1;
    if (algptype != V_ASN1_SEQUENCE) {
        RSAerr(RSA_F_RSA_PARAM_DECODE, RSA_R_INVALID_PSS_PARAMETERS);
        return 0;
    }
    rsa->pss = rsa_pss_decode(alg);
    if (rsa->pss == NULL)
        return 0;
    return 1;
}