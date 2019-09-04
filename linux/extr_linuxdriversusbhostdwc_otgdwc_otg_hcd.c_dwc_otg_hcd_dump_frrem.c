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
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */

void dwc_otg_hcd_dump_frrem(dwc_otg_hcd_t * hcd)
{
#if 0
	DWC_PRINTF("Frame remaining at SOF:\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->frrem_samples, hcd->frrem_accum,
		   (hcd->frrem_samples > 0) ?
		   hcd->frrem_accum / hcd->frrem_samples : 0);

	DWC_PRINTF("\n");
	DWC_PRINTF("Frame remaining at start_transfer (uframe 7):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->core_if->hfnum_7_samples,
		   hcd->core_if->hfnum_7_frrem_accum,
		   (hcd->core_if->hfnum_7_samples >
		    0) ? hcd->core_if->hfnum_7_frrem_accum /
		   hcd->core_if->hfnum_7_samples : 0);
	DWC_PRINTF("Frame remaining at start_transfer (uframe 0):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->core_if->hfnum_0_samples,
		   hcd->core_if->hfnum_0_frrem_accum,
		   (hcd->core_if->hfnum_0_samples >
		    0) ? hcd->core_if->hfnum_0_frrem_accum /
		   hcd->core_if->hfnum_0_samples : 0);
	DWC_PRINTF("Frame remaining at start_transfer (uframe 1-6):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->core_if->hfnum_other_samples,
		   hcd->core_if->hfnum_other_frrem_accum,
		   (hcd->core_if->hfnum_other_samples >
		    0) ? hcd->core_if->hfnum_other_frrem_accum /
		   hcd->core_if->hfnum_other_samples : 0);

	DWC_PRINTF("\n");
	DWC_PRINTF("Frame remaining at sample point A (uframe 7):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_7_samples_a, hcd->hfnum_7_frrem_accum_a,
		   (hcd->hfnum_7_samples_a > 0) ?
		   hcd->hfnum_7_frrem_accum_a / hcd->hfnum_7_samples_a : 0);
	DWC_PRINTF("Frame remaining at sample point A (uframe 0):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_0_samples_a, hcd->hfnum_0_frrem_accum_a,
		   (hcd->hfnum_0_samples_a > 0) ?
		   hcd->hfnum_0_frrem_accum_a / hcd->hfnum_0_samples_a : 0);
	DWC_PRINTF("Frame remaining at sample point A (uframe 1-6):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_other_samples_a, hcd->hfnum_other_frrem_accum_a,
		   (hcd->hfnum_other_samples_a > 0) ?
		   hcd->hfnum_other_frrem_accum_a /
		   hcd->hfnum_other_samples_a : 0);

	DWC_PRINTF("\n");
	DWC_PRINTF("Frame remaining at sample point B (uframe 7):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_7_samples_b, hcd->hfnum_7_frrem_accum_b,
		   (hcd->hfnum_7_samples_b > 0) ?
		   hcd->hfnum_7_frrem_accum_b / hcd->hfnum_7_samples_b : 0);
	DWC_PRINTF("Frame remaining at sample point B (uframe 0):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_0_samples_b, hcd->hfnum_0_frrem_accum_b,
		   (hcd->hfnum_0_samples_b > 0) ?
		   hcd->hfnum_0_frrem_accum_b / hcd->hfnum_0_samples_b : 0);
	DWC_PRINTF("Frame remaining at sample point B (uframe 1-6):\n");
	DWC_PRINTF("  samples %u, accum %llu, avg %llu\n",
		   hcd->hfnum_other_samples_b, hcd->hfnum_other_frrem_accum_b,
		   (hcd->hfnum_other_samples_b > 0) ?
		   hcd->hfnum_other_frrem_accum_b /
		   hcd->hfnum_other_samples_b : 0);
#endif
}