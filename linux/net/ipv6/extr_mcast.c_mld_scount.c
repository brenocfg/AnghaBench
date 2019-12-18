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
struct ip6_sf_list {struct ip6_sf_list* sf_next; } ;
struct ifmcaddr6 {struct ip6_sf_list* mca_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_in (struct ifmcaddr6*,struct ip6_sf_list*,int,int,int) ; 

__attribute__((used)) static int
mld_scount(struct ifmcaddr6 *pmc, int type, int gdeleted, int sdeleted)
{
	struct ip6_sf_list *psf;
	int scount = 0;

	for (psf = pmc->mca_sources; psf; psf = psf->sf_next) {
		if (!is_in(pmc, psf, type, gdeleted, sdeleted))
			continue;
		scount++;
	}
	return scount;
}