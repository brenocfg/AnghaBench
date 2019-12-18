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
struct TYPE_5__ {int flags; int /*<<< orphan*/  enc_offset; } ;
struct TYPE_4__ {TYPE_2__* funcs; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_ENCODING ;
typedef  TYPE_2__ ASN1_AUX ;

/* Variables and functions */
 int ASN1_AFLG_ENCODING ; 
 int /*<<< orphan*/ * offset2ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ASN1_ENCODING *asn1_get_enc_ptr(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    const ASN1_AUX *aux;

    if (pval == NULL || *pval == NULL)
        return NULL;
    aux = it->funcs;
    if (aux == NULL || (aux->flags & ASN1_AFLG_ENCODING) == 0)
        return NULL;
    return offset2ptr(*pval, aux->enc_offset);
}