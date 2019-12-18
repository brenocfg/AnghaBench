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
struct TYPE_4__ {int /*<<< orphan*/ * other; } ;
struct TYPE_5__ {TYPE_1__ infoValue; } ;
typedef  TYPE_2__ OSSL_CMP_ITAV ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */

ASN1_TYPE *OSSL_CMP_ITAV_get0_value(const OSSL_CMP_ITAV *itav)
{
    if (itav == NULL)
        return NULL;
    return itav->infoValue.other;
}