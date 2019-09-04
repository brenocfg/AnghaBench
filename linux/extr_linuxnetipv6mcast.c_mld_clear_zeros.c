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

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip6_sf_list*) ; 

__attribute__((used)) static void mld_clear_zeros(struct ip6_sf_list **ppsf)
{
	struct ip6_sf_list *psf_prev, *psf_next, *psf;

	psf_prev = NULL;
	for (psf = *ppsf; psf; psf = psf_next) {
		psf_next = psf->sf_next;
		if (psf->sf_crcount == 0) {
			if (psf_prev)
				psf_prev->sf_next = psf->sf_next;
			else
				*ppsf = psf->sf_next;
			kfree(psf);
		} else
			psf_prev = psf;
	}
}