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
struct TYPE_3__ {int /*<<< orphan*/  attrib; } ;
typedef  TYPE_1__ PKCS12_SAFEBAG ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  const* PKCS12_get_attr_gen (int /*<<< orphan*/ ,int) ; 

const ASN1_TYPE *PKCS12_SAFEBAG_get0_attr(const PKCS12_SAFEBAG *bag,
                                          int attr_nid)
{
    return PKCS12_get_attr_gen(bag->attrib, attr_nid);
}