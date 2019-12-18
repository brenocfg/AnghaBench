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
struct ar934x_nfc {unsigned int buf_size; int /*<<< orphan*/ * buf; int /*<<< orphan*/  parent; int /*<<< orphan*/  buf_dma; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int ar934x_nfc_alloc_buf(struct ar934x_nfc *nfc, unsigned size)
{
	nfc->buf = dma_alloc_coherent(nfc->parent, size,
				      &nfc->buf_dma, GFP_KERNEL);
	if (nfc->buf == NULL) {
		dev_err(nfc->parent, "no memory for DMA buffer\n");
		return -ENOMEM;
	}

	nfc->buf_size = size;
	nfc_dbg(nfc, "buf:%p size:%u\n", nfc->buf, nfc->buf_size);

	return 0;
}