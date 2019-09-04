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
struct TYPE_8__ {int /*<<< orphan*/ * DATA; } ;
union usb_reg_access {scalar_t__ dw; TYPE_4__ byte; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct TYPE_5__ {int actual; scalar_t__ buf; } ;
struct nbu2ss_req {int div_len; TYPE_1__ req; scalar_t__ dma_flag; } ;
struct TYPE_7__ {int maxpacket; } ;
struct nbu2ss_ep {int epnum; TYPE_3__ ep; } ;
struct fc_regs {TYPE_2__* EP_REGS; } ;
struct TYPE_6__ {int /*<<< orphan*/  EP_WRITE; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nbu2ss_ep_in_end (struct nbu2ss_udc*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int _nbu2ss_epn_in_pio(
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
	union usb_reg_access	*p_buf_32 = NULL;
	int		result = 0;
	struct fc_regs	*preg = udc->p_regs;

	if (req->dma_flag)
		return 1;		/* DMA is forwarded */

	if (length > 0) {
		p_buffer = (u8 *)req->req.buf;
		p_buf_32 = (union usb_reg_access *)(p_buffer + req->req.actual);

		i_word_length = length / sizeof(u32);
		if (i_word_length > 0) {
			for (i = 0; i < i_word_length; i++) {
				_nbu2ss_writel(
					&preg->EP_REGS[ep->epnum - 1].EP_WRITE
					, p_buf_32->dw
				);

				p_buf_32++;
			}
			result = i_word_length * sizeof(u32);
		}
	}

	if (result != ep->ep.maxpacket) {
		data = length - result;
		temp_32.dw = 0;
		for (i = 0 ; i < data ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];

		_nbu2ss_ep_in_end(udc, ep->epnum, temp_32.dw, data);
		result += data;
	}

	req->div_len = result;

	return result;
}