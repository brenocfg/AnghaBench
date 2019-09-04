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
struct ip6_sf_list {scalar_t__ sf_crcount; struct ip6_sf_list* sf_next; } ;
struct inet6_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  mc_ifc_count; int /*<<< orphan*/  mc_qrv; struct ifmcaddr6* mc_list; } ;
struct in6_addr {int dummy; } ;
struct ifmcaddr6 {scalar_t__* mca_sfcount; size_t mca_sfmode; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  idev; struct ip6_sf_list* mca_sources; int /*<<< orphan*/  mca_crcount; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ESRCH ; 
 size_t MCAST_EXCLUDE ; 
 size_t MCAST_INCLUDE ; 
 int ip6_mc_del1_src (struct ifmcaddr6*,int,struct in6_addr const*) ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mld_ifc_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sf_markstate (struct ifmcaddr6*) ; 
 scalar_t__ sf_setstate (struct ifmcaddr6*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ip6_mc_del_src(struct inet6_dev *idev, const struct in6_addr *pmca,
			  int sfmode, int sfcount, const struct in6_addr *psfsrc,
			  int delta)
{
	struct ifmcaddr6 *pmc;
	int	changerec = 0;
	int	i, err;

	if (!idev)
		return -ENODEV;
	read_lock_bh(&idev->lock);
	for (pmc = idev->mc_list; pmc; pmc = pmc->next) {
		if (ipv6_addr_equal(pmca, &pmc->mca_addr))
			break;
	}
	if (!pmc) {
		/* MCA not found?? bug */
		read_unlock_bh(&idev->lock);
		return -ESRCH;
	}
	spin_lock_bh(&pmc->mca_lock);
	sf_markstate(pmc);
	if (!delta) {
		if (!pmc->mca_sfcount[sfmode]) {
			spin_unlock_bh(&pmc->mca_lock);
			read_unlock_bh(&idev->lock);
			return -EINVAL;
		}
		pmc->mca_sfcount[sfmode]--;
	}
	err = 0;
	for (i = 0; i < sfcount; i++) {
		int rv = ip6_mc_del1_src(pmc, sfmode, &psfsrc[i]);

		changerec |= rv > 0;
		if (!err && rv < 0)
			err = rv;
	}
	if (pmc->mca_sfmode == MCAST_EXCLUDE &&
	    pmc->mca_sfcount[MCAST_EXCLUDE] == 0 &&
	    pmc->mca_sfcount[MCAST_INCLUDE]) {
		struct ip6_sf_list *psf;

		/* filter mode change */
		pmc->mca_sfmode = MCAST_INCLUDE;
		pmc->mca_crcount = idev->mc_qrv;
		idev->mc_ifc_count = pmc->mca_crcount;
		for (psf = pmc->mca_sources; psf; psf = psf->sf_next)
			psf->sf_crcount = 0;
		mld_ifc_event(pmc->idev);
	} else if (sf_setstate(pmc) || changerec)
		mld_ifc_event(pmc->idev);
	spin_unlock_bh(&pmc->mca_lock);
	read_unlock_bh(&idev->lock);
	return err;
}