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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int size; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;
typedef  TYPE_1__ ASN1_ITEM ;

/* Variables and functions */
 int BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int INTxx_FLAG_SIGNED ; 

__attribute__((used)) static int uint32_print(BIO *out, const ASN1_VALUE **pval, const ASN1_ITEM *it,
                        int indent, const ASN1_PCTX *pctx)
{
    if ((it->size & INTxx_FLAG_SIGNED) == INTxx_FLAG_SIGNED)
        return BIO_printf(out, "%d\n", **(int32_t **)pval);
    return BIO_printf(out, "%u\n", **(uint32_t **)pval);
}