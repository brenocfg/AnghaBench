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
struct wsm_buf {int /*<<< orphan*/ * begin; int /*<<< orphan*/ * end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 size_t FWLOAD_BLOCK_SIZE ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (size_t,int) ; 
 int /*<<< orphan*/  wsm_buf_reset (struct wsm_buf*) ; 

void wsm_buf_init(struct wsm_buf *buf)
{
	BUG_ON(buf->begin);
	buf->begin = kmalloc(FWLOAD_BLOCK_SIZE, GFP_KERNEL | GFP_DMA);
	buf->end = buf->begin ? &buf->begin[FWLOAD_BLOCK_SIZE] : buf->begin;
	wsm_buf_reset(buf);
}