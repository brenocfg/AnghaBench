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
struct wm_adsp_compr_buf {int irq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_BUFFER_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compr_dbg (struct wm_adsp_compr_buf*,char*,int) ; 
 int /*<<< orphan*/  irq_ack ; 
 int wm_adsp_buffer_write (struct wm_adsp_compr_buf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm_adsp_buffer_reenable_irq(struct wm_adsp_compr_buf *buf)
{
	if (buf->irq_count & 0x01)
		return 0;

	compr_dbg(buf, "Enable IRQ(0x%x) for next fragment\n", buf->irq_count);

	buf->irq_count |= 0x01;

	return wm_adsp_buffer_write(buf, HOST_BUFFER_FIELD(irq_ack),
				    buf->irq_count);
}