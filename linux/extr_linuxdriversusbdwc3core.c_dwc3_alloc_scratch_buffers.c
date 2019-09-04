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
struct dwc3 {int /*<<< orphan*/  scratchbuf; int /*<<< orphan*/  nr_scratch; int /*<<< orphan*/  has_hibernation; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_SCRATCHBUF_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmalloc_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_alloc_scratch_buffers(struct dwc3 *dwc)
{
	if (!dwc->has_hibernation)
		return 0;

	if (!dwc->nr_scratch)
		return 0;

	dwc->scratchbuf = kmalloc_array(dwc->nr_scratch,
			DWC3_SCRATCHBUF_SIZE, GFP_KERNEL);
	if (!dwc->scratchbuf)
		return -ENOMEM;

	return 0;
}