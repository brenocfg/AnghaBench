#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * octet_string; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_TYPE_GET_OCTETSTRING ; 
 int /*<<< orphan*/  ASN1_R_DATA_IS_WRONG ; 
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

int ASN1_TYPE_get_octetstring(const ASN1_TYPE *a, unsigned char *data, int max_len)
{
    int ret, num;
    const unsigned char *p;

    if ((a->type != V_ASN1_OCTET_STRING) || (a->value.octet_string == NULL)) {
        ASN1err(ASN1_F_ASN1_TYPE_GET_OCTETSTRING, ASN1_R_DATA_IS_WRONG);
        return -1;
    }
    p = ASN1_STRING_get0_data(a->value.octet_string);
    ret = ASN1_STRING_length(a->value.octet_string);
    if (ret < max_len)
        num = ret;
    else
        num = max_len;
    memcpy(data, p, num);
    return ret;
}