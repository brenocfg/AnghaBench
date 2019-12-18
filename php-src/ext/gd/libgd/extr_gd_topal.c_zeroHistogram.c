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
typedef  int /*<<< orphan*/  histcell ;
typedef  int /*<<< orphan*/ * hist3d ;

/* Variables and functions */
 int HIST_C0_ELEMS ; 
 int HIST_C1_ELEMS ; 
 int HIST_C2_ELEMS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
zeroHistogram (hist3d histogram)
{
  int i;
  /* Zero the histogram or inverse color map */
  for (i = 0; i < HIST_C0_ELEMS; i++)
    {
      memset (histogram[i],
	      0, HIST_C1_ELEMS * HIST_C2_ELEMS * sizeof (histcell));
    }
}