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
struct TYPE_3__ {int /*<<< orphan*/  const* it; } ;
typedef  TYPE_1__ ASN1_SCTX ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */

const ASN1_ITEM *ASN1_SCTX_get_item(ASN1_SCTX *p)
{
    return p->it;
}