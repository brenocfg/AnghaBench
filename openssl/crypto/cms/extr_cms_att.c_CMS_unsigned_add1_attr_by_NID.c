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
struct TYPE_3__ {int /*<<< orphan*/  unsignedAttrs; } ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */
 scalar_t__ X509at_add1_attr_by_NID (int /*<<< orphan*/ *,int,int,void const*,int) ; 

int CMS_unsigned_add1_attr_by_NID(CMS_SignerInfo *si,
                                  int nid, int type,
                                  const void *bytes, int len)
{
    if (X509at_add1_attr_by_NID(&si->unsignedAttrs, nid, type, bytes, len))
        return 1;
    return 0;
}