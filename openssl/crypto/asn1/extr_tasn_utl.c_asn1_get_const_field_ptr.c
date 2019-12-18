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
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_TEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  const** offset2ptr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

const ASN1_VALUE **asn1_get_const_field_ptr(const ASN1_VALUE **pval,
                                            const ASN1_TEMPLATE *tt)
{
    return offset2ptr(*pval, tt->offset);
}