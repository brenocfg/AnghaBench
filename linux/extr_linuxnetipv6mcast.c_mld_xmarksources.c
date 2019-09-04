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
struct ip6_sf_list {scalar_t__* sf_count; int /*<<< orphan*/  sf_addr; struct ip6_sf_list* sf_next; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {scalar_t__* mca_sfcount; int /*<<< orphan*/  mca_flags; struct ip6_sf_list* mca_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAF_GSQUERY ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mld_xmarksources(struct ifmcaddr6 *pmc, int nsrcs,
			     const struct in6_addr *srcs)
{
	struct ip6_sf_list *psf;
	int i, scount;

	scount = 0;
	for (psf = pmc->mca_sources; psf; psf = psf->sf_next) {
		if (scount == nsrcs)
			break;
		for (i = 0; i < nsrcs; i++) {
			/* skip inactive filters */
			if (psf->sf_count[MCAST_INCLUDE] ||
			    pmc->mca_sfcount[MCAST_EXCLUDE] !=
			    psf->sf_count[MCAST_EXCLUDE])
				break;
			if (ipv6_addr_equal(&srcs[i], &psf->sf_addr)) {
				scount++;
				break;
			}
		}
	}
	pmc->mca_flags &= ~MAF_GSQUERY;
	if (scount == nsrcs)	/* all sources excluded */
		return false;
	return true;
}