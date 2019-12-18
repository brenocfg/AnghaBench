#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  version; } ;
struct TYPE_21__ {TYPE_1__* enc_data; int /*<<< orphan*/  version; } ;
struct TYPE_19__ {TYPE_12__* digest; TYPE_11__* encrypted; TYPE_10__* enveloped; TYPE_7__* signed_and_enveloped; int /*<<< orphan*/ * data; TYPE_8__* sign; } ;
struct TYPE_20__ {TYPE_4__ d; int /*<<< orphan*/ * type; } ;
struct TYPE_18__ {void* content_type; } ;
struct TYPE_17__ {void* content_type; } ;
struct TYPE_16__ {void* content_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  version; } ;
struct TYPE_14__ {TYPE_3__* enc_data; int /*<<< orphan*/  version; } ;
struct TYPE_13__ {TYPE_2__* enc_data; int /*<<< orphan*/  version; } ;
typedef  TYPE_5__ PKCS7 ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
#define  NID_pkcs7_data 133 
#define  NID_pkcs7_digest 132 
#define  NID_pkcs7_encrypted 131 
#define  NID_pkcs7_enveloped 130 
#define  NID_pkcs7_signed 129 
#define  NID_pkcs7_signedAndEnveloped 128 
 void* OBJ_nid2obj (int const) ; 
 TYPE_12__* PKCS7_DIGEST_new () ; 
 TYPE_11__* PKCS7_ENCRYPT_new () ; 
 TYPE_10__* PKCS7_ENVELOPE_new () ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SET_TYPE ; 
 int /*<<< orphan*/  PKCS7_R_UNSUPPORTED_CONTENT_TYPE ; 
 int /*<<< orphan*/  PKCS7_SIGNED_free (TYPE_8__*) ; 
 TYPE_8__* PKCS7_SIGNED_new () ; 
 TYPE_7__* PKCS7_SIGN_ENVELOPE_new () ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PKCS7_set_type(PKCS7 *p7, int type)
{
    ASN1_OBJECT *obj;

    /*
     * PKCS7_content_free(p7);
     */
    obj = OBJ_nid2obj(type);    /* will not fail */

    switch (type) {
    case NID_pkcs7_signed:
        p7->type = obj;
        if ((p7->d.sign = PKCS7_SIGNED_new()) == NULL)
            goto err;
        if (!ASN1_INTEGER_set(p7->d.sign->version, 1)) {
            PKCS7_SIGNED_free(p7->d.sign);
            p7->d.sign = NULL;
            goto err;
        }
        break;
    case NID_pkcs7_data:
        p7->type = obj;
        if ((p7->d.data = ASN1_OCTET_STRING_new()) == NULL)
            goto err;
        break;
    case NID_pkcs7_signedAndEnveloped:
        p7->type = obj;
        if ((p7->d.signed_and_enveloped = PKCS7_SIGN_ENVELOPE_new())
            == NULL)
            goto err;
        if (!ASN1_INTEGER_set(p7->d.signed_and_enveloped->version, 1))
            goto err;
        p7->d.signed_and_enveloped->enc_data->content_type
            = OBJ_nid2obj(NID_pkcs7_data);
        break;
    case NID_pkcs7_enveloped:
        p7->type = obj;
        if ((p7->d.enveloped = PKCS7_ENVELOPE_new())
            == NULL)
            goto err;
        if (!ASN1_INTEGER_set(p7->d.enveloped->version, 0))
            goto err;
        p7->d.enveloped->enc_data->content_type = OBJ_nid2obj(NID_pkcs7_data);
        break;
    case NID_pkcs7_encrypted:
        p7->type = obj;
        if ((p7->d.encrypted = PKCS7_ENCRYPT_new())
            == NULL)
            goto err;
        if (!ASN1_INTEGER_set(p7->d.encrypted->version, 0))
            goto err;
        p7->d.encrypted->enc_data->content_type = OBJ_nid2obj(NID_pkcs7_data);
        break;

    case NID_pkcs7_digest:
        p7->type = obj;
        if ((p7->d.digest = PKCS7_DIGEST_new())
            == NULL)
            goto err;
        if (!ASN1_INTEGER_set(p7->d.digest->version, 0))
            goto err;
        break;
    default:
        PKCS7err(PKCS7_F_PKCS7_SET_TYPE, PKCS7_R_UNSUPPORTED_CONTENT_TYPE);
        goto err;
    }
    return 1;
 err:
    return 0;
}