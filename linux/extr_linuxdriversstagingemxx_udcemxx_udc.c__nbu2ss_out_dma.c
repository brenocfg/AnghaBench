#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct TYPE_4__ {scalar_t__ actual; scalar_t__ dma; } ;
struct nbu2ss_req {int div_len; TYPE_1__ req; scalar_t__ dma_flag; } ;
struct fc_regs {TYPE_3__* EP_REGS; TYPE_2__* EP_DCR; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  EP_DMA_CTRL; int /*<<< orphan*/  EP_LEN_DCNT; int /*<<< orphan*/  EP_PCKT_ADRS; } ;
struct TYPE_5__ {int /*<<< orphan*/  EP_DCR1; int /*<<< orphan*/  EP_DCR2; int /*<<< orphan*/  EP_TADR; } ;

/* Variables and functions */
 size_t DCR1_EPN_DIR0 ; 
 size_t DCR1_EPN_REQEN ; 
 size_t DMA_MAX_COUNT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPN_BURST_SET ; 
 int /*<<< orphan*/  EPN_DMA_EN ; 
 size_t EPN_MPKT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int _nbu2ss_out_dma(
	struct nbu2ss_udc *udc,
	struct nbu2ss_req *req,
	u32		num,
	u32		length
)
{
	dma_addr_t	p_buffer;
	u32		mpkt;
	u32		lmpkt;
	u32		dmacnt;
	u32		burst = 1;
	u32		data;
	int		result = -EINVAL;
	struct fc_regs	*preg = udc->p_regs;

	if (req->dma_flag)
		return 1;		/* DMA is forwarded */

	req->dma_flag = TRUE;
	p_buffer = req->req.dma;
	p_buffer += req->req.actual;

	/* DMA Address */
	_nbu2ss_writel(&preg->EP_DCR[num].EP_TADR, (u32)p_buffer);

	/* Number of transfer packets */
	mpkt = _nbu2ss_readl(&preg->EP_REGS[num].EP_PCKT_ADRS) & EPN_MPKT;
	dmacnt = length / mpkt;
	lmpkt = (length % mpkt) & ~(u32)0x03;

	if (dmacnt > DMA_MAX_COUNT) {
		dmacnt = DMA_MAX_COUNT;
		lmpkt = 0;
	} else if (lmpkt != 0) {
		if (dmacnt == 0)
			burst = 0;	/* Burst OFF */
		dmacnt++;
	}

	data = mpkt | (lmpkt << 16);
	_nbu2ss_writel(&preg->EP_DCR[num].EP_DCR2, data);

	data = ((dmacnt & 0xff) << 16) | DCR1_EPN_DIR0 | DCR1_EPN_REQEN;
	_nbu2ss_writel(&preg->EP_DCR[num].EP_DCR1, data);

	if (burst == 0) {
		_nbu2ss_writel(&preg->EP_REGS[num].EP_LEN_DCNT, 0);
		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_BURST_SET);
	} else {
		_nbu2ss_writel(&preg->EP_REGS[num].EP_LEN_DCNT
				, (dmacnt << 16));
		_nbu2ss_bitset(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_BURST_SET);
	}
	_nbu2ss_bitset(&preg->EP_REGS[num].EP_DMA_CTRL, EPN_DMA_EN);

	result = length & ~(u32)0x03;
	req->div_len = result;

	return result;
}