#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_adapter {int /*<<< orphan*/ * vda_buffer; int /*<<< orphan*/  ppvda_buffer; TYPE_1__* pcid; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long VDA_MAX_BUFFER_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 

int esas2r_write_vda(struct esas2r_adapter *a, const char *buf, long off,
		     int count)
{
	/*
	 * allocate memory for it, if not already done.  once allocated,
	 * we will keep it around until the driver is unloaded.
	 */

	if (!a->vda_buffer) {
		dma_addr_t dma_addr;
		a->vda_buffer = (u8 *)dma_alloc_coherent(&a->pcid->dev,
							 (size_t)
							 VDA_MAX_BUFFER_SIZE,
							 &dma_addr,
							 GFP_KERNEL);

		a->ppvda_buffer = dma_addr;
	}

	if (!a->vda_buffer)
		return -ENOMEM;

	if (off > VDA_MAX_BUFFER_SIZE)
		return 0;

	if (count + off > VDA_MAX_BUFFER_SIZE)
		count = VDA_MAX_BUFFER_SIZE - off;

	if (count < 1)
		return 0;

	memcpy(a->vda_buffer + off, buf, count);

	return count;
}