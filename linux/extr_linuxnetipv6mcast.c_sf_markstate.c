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
struct ip6_sf_list {int sf_oldin; int* sf_count; struct ip6_sf_list* sf_next; } ;
struct ifmcaddr6 {int* mca_sfcount; struct ip6_sf_list* mca_sources; } ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 

__attribute__((used)) static void sf_markstate(struct ifmcaddr6 *pmc)
{
	struct ip6_sf_list *psf;
	int mca_xcount = pmc->mca_sfcount[MCAST_EXCLUDE];

	for (psf = pmc->mca_sources; psf; psf = psf->sf_next)
		if (pmc->mca_sfcount[MCAST_EXCLUDE]) {
			psf->sf_oldin = mca_xcount ==
				psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		} else
			psf->sf_oldin = psf->sf_count[MCAST_INCLUDE] != 0;
}