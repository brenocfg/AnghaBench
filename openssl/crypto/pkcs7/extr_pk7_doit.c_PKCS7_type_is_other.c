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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ PKCS7 ;

/* Variables and functions */
#define  NID_pkcs7_data 133 
#define  NID_pkcs7_digest 132 
#define  NID_pkcs7_encrypted 131 
#define  NID_pkcs7_enveloped 130 
#define  NID_pkcs7_signed 129 
#define  NID_pkcs7_signedAndEnveloped 128 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int PKCS7_type_is_other(PKCS7 *p7)
{
    int isOther = 1;

    int nid = OBJ_obj2nid(p7->type);

    switch (nid) {
    case NID_pkcs7_data:
    case NID_pkcs7_signed:
    case NID_pkcs7_enveloped:
    case NID_pkcs7_signedAndEnveloped:
    case NID_pkcs7_digest:
    case NID_pkcs7_encrypted:
        isOther = 0;
        break;
    default:
        isOther = 1;
    }

    return isOther;

}