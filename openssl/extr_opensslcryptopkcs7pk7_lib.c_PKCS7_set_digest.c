#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__* digest; } ;
struct TYPE_11__ {TYPE_1__ d; } ;
struct TYPE_10__ {int /*<<< orphan*/  algorithm; TYPE_7__* parameter; } ;
struct TYPE_9__ {TYPE_3__* md; } ;
typedef  TYPE_4__ PKCS7 ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 TYPE_7__* ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_MD_nid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SET_DIGEST ; 
 int /*<<< orphan*/  PKCS7_R_WRONG_CONTENT_TYPE ; 
 scalar_t__ PKCS7_type_is_digest (TYPE_4__*) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 

int PKCS7_set_digest(PKCS7 *p7, const EVP_MD *md)
{
    if (PKCS7_type_is_digest(p7)) {
        if ((p7->d.digest->md->parameter = ASN1_TYPE_new()) == NULL) {
            PKCS7err(PKCS7_F_PKCS7_SET_DIGEST, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        p7->d.digest->md->parameter->type = V_ASN1_NULL;
        p7->d.digest->md->algorithm = OBJ_nid2obj(EVP_MD_nid(md));
        return 1;
    }

    PKCS7err(PKCS7_F_PKCS7_SET_DIGEST, PKCS7_R_WRONG_CONTENT_TYPE);
    return 1;
}