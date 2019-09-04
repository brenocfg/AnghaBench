#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_FLAG_NDEF ; 
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (scalar_t__,int /*<<< orphan*/ ) ; 

void ASN1_STRING_clear_free(ASN1_STRING *a)
{
    if (a == NULL)
        return;
    if (a->data && !(a->flags & ASN1_STRING_FLAG_NDEF))
        OPENSSL_cleanse(a->data, a->length);
    ASN1_STRING_free(a);
}