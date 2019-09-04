#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * DATA; } ;
union usb_reg_access {TYPE_2__ byte; void* dw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct TYPE_7__ {int actual; scalar_t__ length; scalar_t__ buf; } ;
struct nbu2ss_req {TYPE_3__ req; scalar_t__ dma_flag; } ;
struct TYPE_8__ {int maxpacket; } ;
struct nbu2ss_ep {int epnum; TYPE_4__ ep; } ;
struct fc_regs {TYPE_1__* EP_REGS; } ;
struct TYPE_5__ {int /*<<< orphan*/  EP_READ; } ;

/* Variables and functions */
 void* _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nbu2ss_epn_out_pio(
	struct nbu2ss_udc *udc,
	struct nbu2ss_ep *ep,
	struct nbu2ss_req *req,
	u32		length
)
{
	u8		*p_buffer;
	u32		i;
	u32		data;
	u32		i_word_length;
	union usb_reg_access	temp_32;
	union usb_reg_access	*p_buf_32;
	int		result = 0;
	struct fc_regs	*preg = udc->p_regs;

	if (req->dma_flag)
		return 1;		/* DMA is forwarded */

	if (length == 0)
		return 0;

	p_buffer = (u8 *)req->req.buf;
	p_buf_32 = (union usb_reg_access *)(p_buffer + req->req.actual);

	i_word_length = length / sizeof(u32);
	if (i_word_length > 0) {
		/*---------------------------------------------------------*/
		/* Copy of every four bytes */
		for (i = 0; i < i_word_length; i++) {
			p_buf_32->dw =
			_nbu2ss_readl(&preg->EP_REGS[ep->epnum - 1].EP_READ);
			p_buf_32++;
		}
		result = i_word_length * sizeof(u32);
	}

	data = length - result;
	if (data > 0) {
		/*---------------------------------------------------------*/
		/* Copy of fraction byte */
		temp_32.dw =
			_nbu2ss_readl(&preg->EP_REGS[ep->epnum - 1].EP_READ);
		for (i = 0 ; i < data ; i++)
			p_buf_32->byte.DATA[i] = temp_32.byte.DATA[i];
		result += data;
	}

	req->req.actual += result;

	if ((req->req.actual == req->req.length) ||
	    ((req->req.actual % ep->ep.maxpacket) != 0)) {
		result = 0;
	}

	return result;
}