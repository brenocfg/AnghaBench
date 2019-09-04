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
struct ip6_sf_list {int /*<<< orphan*/  sf_crcount; int /*<<< orphan*/ * sf_count; int /*<<< orphan*/  sf_gsresp; } ;
struct ifmcaddr6 {int mca_flags; size_t mca_sfmode; int /*<<< orphan*/ * mca_sfcount; } ;

/* Variables and functions */
 int MAF_GSQUERY ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
#define  MLD2_ALLOW_NEW_SOURCES 133 
#define  MLD2_BLOCK_OLD_SOURCES 132 
#define  MLD2_CHANGE_TO_EXCLUDE 131 
#define  MLD2_CHANGE_TO_INCLUDE 130 
#define  MLD2_MODE_IS_EXCLUDE 129 
#define  MLD2_MODE_IS_INCLUDE 128 

__attribute__((used)) static bool is_in(struct ifmcaddr6 *pmc, struct ip6_sf_list *psf, int type,
		  int gdeleted, int sdeleted)
{
	switch (type) {
	case MLD2_MODE_IS_INCLUDE:
	case MLD2_MODE_IS_EXCLUDE:
		if (gdeleted || sdeleted)
			return false;
		if (!((pmc->mca_flags & MAF_GSQUERY) && !psf->sf_gsresp)) {
			if (pmc->mca_sfmode == MCAST_INCLUDE)
				return true;
			/* don't include if this source is excluded
			 * in all filters
			 */
			if (psf->sf_count[MCAST_INCLUDE])
				return type == MLD2_MODE_IS_INCLUDE;
			return pmc->mca_sfcount[MCAST_EXCLUDE] ==
				psf->sf_count[MCAST_EXCLUDE];
		}
		return false;
	case MLD2_CHANGE_TO_INCLUDE:
		if (gdeleted || sdeleted)
			return false;
		return psf->sf_count[MCAST_INCLUDE] != 0;
	case MLD2_CHANGE_TO_EXCLUDE:
		if (gdeleted || sdeleted)
			return false;
		if (pmc->mca_sfcount[MCAST_EXCLUDE] == 0 ||
		    psf->sf_count[MCAST_INCLUDE])
			return false;
		return pmc->mca_sfcount[MCAST_EXCLUDE] ==
			psf->sf_count[MCAST_EXCLUDE];
	case MLD2_ALLOW_NEW_SOURCES:
		if (gdeleted || !psf->sf_crcount)
			return false;
		return (pmc->mca_sfmode == MCAST_INCLUDE) ^ sdeleted;
	case MLD2_BLOCK_OLD_SOURCES:
		if (pmc->mca_sfmode == MCAST_INCLUDE)
			return gdeleted || (psf->sf_crcount && sdeleted);
		return psf->sf_crcount && !gdeleted && !sdeleted;
	}
	return false;
}