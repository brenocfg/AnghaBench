#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nid; int flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  unsignedAttrs; int /*<<< orphan*/  signedAttrs; } ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_ATTR_F_SIGNED ; 
 int /*<<< orphan*/  CMS_ATTR_F_UNSIGNED ; 
 int /*<<< orphan*/  CMS_F_CMS_SI_CHECK_ATTRIBUTES ; 
 int /*<<< orphan*/  CMS_R_ATTRIBUTE_ERROR ; 
 scalar_t__ CMS_signed_get_attr_count (TYPE_1__ const*) ; 
 scalar_t__ CMS_unsigned_get_attr_count (TYPE_1__ const*) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSSL_NELEM (TYPE_2__*) ; 
 TYPE_2__* cms_attribute_properties ; 
 int /*<<< orphan*/  cms_check_attribute (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int CMS_si_check_attributes(const CMS_SignerInfo *si)
{
    int i;
    int have_signed_attrs = (CMS_signed_get_attr_count(si) > 0);
    int have_unsigned_attrs = (CMS_unsigned_get_attr_count(si) > 0);

    for (i = 0; i < (int)OSSL_NELEM(cms_attribute_properties); ++i) {
        int nid = cms_attribute_properties[i].nid;
        int flags = cms_attribute_properties[i].flags;

        if (!cms_check_attribute(nid, flags, CMS_ATTR_F_SIGNED,
                                 si->signedAttrs, have_signed_attrs)
            || !cms_check_attribute(nid, flags, CMS_ATTR_F_UNSIGNED,
                                    si->unsignedAttrs, have_unsigned_attrs)) {
            CMSerr(CMS_F_CMS_SI_CHECK_ATTRIBUTES, CMS_R_ATTRIBUTE_ERROR);
            return 0;
        }
    }
    return 1;
}