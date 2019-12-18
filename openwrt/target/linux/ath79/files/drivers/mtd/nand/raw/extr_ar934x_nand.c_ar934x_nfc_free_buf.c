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
struct ar934x_nfc {int /*<<< orphan*/  buf_dma; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar934x_nfc_free_buf(struct ar934x_nfc *nfc)
{
	dma_free_coherent(nfc->parent, nfc->buf_size, nfc->buf, nfc->buf_dma);
}