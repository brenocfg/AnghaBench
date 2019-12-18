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
struct TYPE_4__ {int flags; struct TYPE_4__* data; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_FLAG_NDEF ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void asn1_string_embed_free(ASN1_STRING *a, int embed)
{
    if (a == NULL)
        return;
    if (!(a->flags & ASN1_STRING_FLAG_NDEF))
        OPENSSL_free(a->data);
    if (embed == 0)
        OPENSSL_free(a);
}