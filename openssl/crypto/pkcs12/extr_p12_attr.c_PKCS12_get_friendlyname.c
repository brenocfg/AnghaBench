#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bmpstring; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ value; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PKCS12_SAFEBAG ;
typedef  TYPE_3__ ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  NID_friendlyName ; 
 char* OPENSSL_uni2utf8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* PKCS12_SAFEBAG_get0_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ V_ASN1_BMPSTRING ; 

char *PKCS12_get_friendlyname(PKCS12_SAFEBAG *bag)
{
    const ASN1_TYPE *atype;

    if ((atype = PKCS12_SAFEBAG_get0_attr(bag, NID_friendlyName)) == NULL)
        return NULL;
    if (atype->type != V_ASN1_BMPSTRING)
        return NULL;
    return OPENSSL_uni2utf8(atype->value.bmpstring->data,
                            atype->value.bmpstring->length);
}