#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* get_asn1_parameters ) (TYPE_1__*,int /*<<< orphan*/ *) ;int flags; int /*<<< orphan*/  nid; int /*<<< orphan*/ * prov; } ;
struct TYPE_8__ {TYPE_2__* cipher; } ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;
typedef  TYPE_2__ EVP_CIPHER ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int EVP_CIPHER_get_asn1_iv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_mode (TYPE_2__ const*) ; 
#define  EVP_CIPH_CCM_MODE 132 
 int EVP_CIPH_FLAG_DEFAULT_ASN1 ; 
#define  EVP_CIPH_GCM_MODE 131 
#define  EVP_CIPH_OCB_MODE 130 
#define  EVP_CIPH_WRAP_MODE 129 
#define  EVP_CIPH_XTS_MODE 128 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_ASN1_TO_PARAM ; 
 int /*<<< orphan*/  EVP_R_CIPHER_PARAMETER_ERROR ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_CIPHER ; 
 TYPE_2__* EVP_get_cipherbynid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

int EVP_CIPHER_asn1_to_param(EVP_CIPHER_CTX *c, ASN1_TYPE *type)
{
    int ret;
    const EVP_CIPHER *cipher = c->cipher;

    if (cipher->prov != NULL) {
        /*
         * The cipher has come from a provider and won't have the default flags.
         * Find the implicit form so we can check the flags.
         */
        cipher = EVP_get_cipherbynid(cipher->nid);
        if (cipher == NULL)
            return -1;
    }

    if (cipher->get_asn1_parameters != NULL)
        ret = cipher->get_asn1_parameters(c, type);
    else if (cipher->flags & EVP_CIPH_FLAG_DEFAULT_ASN1) {
        switch (EVP_CIPHER_mode(cipher)) {

        case EVP_CIPH_WRAP_MODE:
            ret = 1;
            break;

        case EVP_CIPH_GCM_MODE:
        case EVP_CIPH_CCM_MODE:
        case EVP_CIPH_XTS_MODE:
        case EVP_CIPH_OCB_MODE:
            ret = -2;
            break;

        default:
            ret = EVP_CIPHER_get_asn1_iv(c, type);
            break;
        }
    } else
        ret = -1;
    if (ret <= 0)
        EVPerr(EVP_F_EVP_CIPHER_ASN1_TO_PARAM, ret == -2 ?
               EVP_R_UNSUPPORTED_CIPHER :
               EVP_R_CIPHER_PARAMETER_ERROR);
    if (ret < -1)
        ret = -1;
    return ret;
}