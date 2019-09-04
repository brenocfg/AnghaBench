#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nlattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ MACSEC_KEYID_LEN ; 
 int MACSEC_NUM_AN ; 
 size_t MACSEC_SA_ATTR_ACTIVE ; 
 size_t MACSEC_SA_ATTR_AN ; 
 size_t MACSEC_SA_ATTR_KEY ; 
 size_t MACSEC_SA_ATTR_KEYID ; 
 size_t MACSEC_SA_ATTR_PN ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static bool validate_add_rxsa(struct nlattr **attrs)
{
	if (!attrs[MACSEC_SA_ATTR_AN] ||
	    !attrs[MACSEC_SA_ATTR_KEY] ||
	    !attrs[MACSEC_SA_ATTR_KEYID])
		return false;

	if (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_NUM_AN)
		return false;

	if (attrs[MACSEC_SA_ATTR_PN] && nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		return false;

	if (attrs[MACSEC_SA_ATTR_ACTIVE]) {
		if (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			return false;
	}

	if (nla_len(attrs[MACSEC_SA_ATTR_KEYID]) != MACSEC_KEYID_LEN)
		return false;

	return true;
}