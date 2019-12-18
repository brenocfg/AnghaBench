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
struct ip_sf_list {struct ip_sf_list* sf_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip_sf_list*) ; 

__attribute__((used)) static void ip_sf_list_clear_all(struct ip_sf_list *psf)
{
	struct ip_sf_list *next;

	while (psf) {
		next = psf->sf_next;
		kfree(psf);
		psf = next;
	}
}