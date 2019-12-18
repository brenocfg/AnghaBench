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
struct TYPE_3__ {int /*<<< orphan*/  signedAttrs; } ;
typedef  TYPE_1__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ X509at_add1_attr_by_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,void const*,int) ; 

int CMS_signed_add1_attr_by_OBJ(CMS_SignerInfo *si,
                                const ASN1_OBJECT *obj, int type,
                                const void *bytes, int len)
{
    if (X509at_add1_attr_by_OBJ(&si->signedAttrs, obj, type, bytes, len))
        return 1;
    return 0;
}