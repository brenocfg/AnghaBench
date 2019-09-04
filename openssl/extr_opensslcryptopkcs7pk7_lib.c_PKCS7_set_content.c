#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* digest; TYPE_1__* sign; } ;
struct TYPE_11__ {TYPE_2__ d; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_4__* contents; } ;
struct TYPE_8__ {TYPE_4__* contents; } ;
typedef  TYPE_4__ PKCS7 ;

/* Variables and functions */
#define  NID_pkcs7_data 133 
#define  NID_pkcs7_digest 132 
#define  NID_pkcs7_encrypted 131 
#define  NID_pkcs7_enveloped 130 
#define  NID_pkcs7_signed 129 
#define  NID_pkcs7_signedAndEnveloped 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SET_CONTENT ; 
 int /*<<< orphan*/  PKCS7_R_UNSUPPORTED_CONTENT_TYPE ; 
 int /*<<< orphan*/  PKCS7_free (TYPE_4__*) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PKCS7_set_content(PKCS7 *p7, PKCS7 *p7_data)
{
    int i;

    i = OBJ_obj2nid(p7->type);
    switch (i) {
    case NID_pkcs7_signed:
        PKCS7_free(p7->d.sign->contents);
        p7->d.sign->contents = p7_data;
        break;
    case NID_pkcs7_digest:
        PKCS7_free(p7->d.digest->contents);
        p7->d.digest->contents = p7_data;
        break;
    case NID_pkcs7_data:
    case NID_pkcs7_enveloped:
    case NID_pkcs7_signedAndEnveloped:
    case NID_pkcs7_encrypted:
    default:
        PKCS7err(PKCS7_F_PKCS7_SET_CONTENT, PKCS7_R_UNSUPPORTED_CONTENT_TYPE);
        goto err;
    }
    return 1;
 err:
    return 0;
}