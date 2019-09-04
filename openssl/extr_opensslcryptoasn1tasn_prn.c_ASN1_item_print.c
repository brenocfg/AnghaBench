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
struct TYPE_9__ {char* sname; } ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_PCTX ;
typedef  TYPE_2__ ASN1_ITEM ;

/* Variables and functions */
 int ASN1_PCTX_FLAGS_NO_STRUCT_NAME ; 
 int asn1_item_print_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,TYPE_2__ const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 TYPE_1__ default_pctx ; 

int ASN1_item_print(BIO *out, const ASN1_VALUE *ifld, int indent,
                    const ASN1_ITEM *it, const ASN1_PCTX *pctx)
{
    const char *sname;
    if (pctx == NULL)
        pctx = &default_pctx;
    if (pctx->flags & ASN1_PCTX_FLAGS_NO_STRUCT_NAME)
        sname = NULL;
    else
        sname = it->sname;
    return asn1_item_print_ctx(out, &ifld, indent, it, NULL, sname, 0, pctx);
}