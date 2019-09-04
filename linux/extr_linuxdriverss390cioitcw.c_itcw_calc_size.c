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
struct tsb {int dummy; } ;
struct tidaw {int dummy; } ;
struct tcw {int dummy; } ;
struct itcw {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ TCCB_MAX_SIZE ; 

size_t itcw_calc_size(int intrg, int max_tidaws, int intrg_max_tidaws)
{
	size_t len;
	int cross_count;

	/* Main data. */
	len = sizeof(struct itcw);
	len += /* TCW */ sizeof(struct tcw) + /* TCCB */ TCCB_MAX_SIZE +
	       /* TSB */ sizeof(struct tsb) +
	       /* TIDAL */ max_tidaws * sizeof(struct tidaw);
	/* Interrogate data. */
	if (intrg) {
		len += /* TCW */ sizeof(struct tcw) + /* TCCB */ TCCB_MAX_SIZE +
		       /* TSB */ sizeof(struct tsb) +
		       /* TIDAL */ intrg_max_tidaws * sizeof(struct tidaw);
	}

	/* Maximum required alignment padding. */
	len += /* Initial TCW */ 63 + /* Interrogate TCCB */ 7;

	/* TIDAW lists may not cross a 4k boundary. To cross a
	 * boundary we need to add a TTIC TIDAW. We need to reserve
	 * one additional TIDAW for a TTIC that we may need to add due
	 * to the placement of the data chunk in memory, and a further
	 * TIDAW for each page boundary that the TIDAW list may cross
	 * due to it's own size.
	 */
	if (max_tidaws) {
		cross_count = 1 + ((max_tidaws * sizeof(struct tidaw) - 1)
				   >> PAGE_SHIFT);
		len += cross_count * sizeof(struct tidaw);
	}
	if (intrg_max_tidaws) {
		cross_count = 1 + ((intrg_max_tidaws * sizeof(struct tidaw) - 1)
				   >> PAGE_SHIFT);
		len += cross_count * sizeof(struct tidaw);
	}
	return len;
}