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
typedef  int /*<<< orphan*/  uint32_t ;
struct csio_sge {int /*<<< orphan*/ * sge_fl_buf_size; } ;
struct csio_dma_buf {int paddr; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
csio_wr_fl_bufsz(struct csio_sge *sge, struct csio_dma_buf *buf)
{
	return sge->sge_fl_buf_size[buf->paddr & 0xF];
}