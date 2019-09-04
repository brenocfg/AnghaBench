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
struct in6_addr {int dummy; } ;
struct ip6_sf_list {int /*<<< orphan*/ * sf_count; struct ip6_sf_list* sf_next; struct in6_addr sf_addr; } ;
struct ifmcaddr6 {struct ip6_sf_list* mca_sources; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,struct in6_addr const*) ; 
 struct ip6_sf_list* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6_mc_add1_src(struct ifmcaddr6 *pmc, int sfmode,
	const struct in6_addr *psfsrc)
{
	struct ip6_sf_list *psf, *psf_prev;

	psf_prev = NULL;
	for (psf = pmc->mca_sources; psf; psf = psf->sf_next) {
		if (ipv6_addr_equal(&psf->sf_addr, psfsrc))
			break;
		psf_prev = psf;
	}
	if (!psf) {
		psf = kzalloc(sizeof(*psf), GFP_ATOMIC);
		if (!psf)
			return -ENOBUFS;

		psf->sf_addr = *psfsrc;
		if (psf_prev) {
			psf_prev->sf_next = psf;
		} else
			pmc->mca_sources = psf;
	}
	psf->sf_count[sfmode]++;
	return 0;
}