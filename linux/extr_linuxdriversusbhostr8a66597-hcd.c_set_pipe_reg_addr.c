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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ pipenum; } ;
struct r8a66597_pipe {unsigned long fifoaddr; unsigned long fifosel; unsigned long fifoctr; int /*<<< orphan*/  pipetrn; int /*<<< orphan*/  pipetre; int /*<<< orphan*/  pipectr; TYPE_1__ info; } ;

/* Variables and functions */
 unsigned long const CFIFO ; 
 unsigned long const CFIFOCTR ; 
 unsigned long const CFIFOSEL ; 
 unsigned long const D0FIFO ; 
 unsigned long const D0FIFOCTR ; 
 unsigned long const D0FIFOSEL ; 
 unsigned long const D1FIFO ; 
 unsigned long const D1FIFOCTR ; 
 unsigned long const D1FIFOSEL ; 
 int /*<<< orphan*/  DCPCTR ; 
 size_t R8A66597_PIPE_NO_DMA ; 
 scalar_t__ check_bulk_or_isoc (scalar_t__) ; 
 int /*<<< orphan*/  get_pipectr_addr (scalar_t__) ; 
 int /*<<< orphan*/  get_pipetre_addr (scalar_t__) ; 
 int /*<<< orphan*/  get_pipetrn_addr (scalar_t__) ; 

__attribute__((used)) static void set_pipe_reg_addr(struct r8a66597_pipe *pipe, u8 dma_ch)
{
	u16 pipenum = pipe->info.pipenum;
	const unsigned long fifoaddr[] = {D0FIFO, D1FIFO, CFIFO};
	const unsigned long fifosel[] = {D0FIFOSEL, D1FIFOSEL, CFIFOSEL};
	const unsigned long fifoctr[] = {D0FIFOCTR, D1FIFOCTR, CFIFOCTR};

	if (dma_ch > R8A66597_PIPE_NO_DMA)	/* dma fifo not use? */
		dma_ch = R8A66597_PIPE_NO_DMA;

	pipe->fifoaddr = fifoaddr[dma_ch];
	pipe->fifosel = fifosel[dma_ch];
	pipe->fifoctr = fifoctr[dma_ch];

	if (pipenum == 0)
		pipe->pipectr = DCPCTR;
	else
		pipe->pipectr = get_pipectr_addr(pipenum);

	if (check_bulk_or_isoc(pipenum)) {
		pipe->pipetre = get_pipetre_addr(pipenum);
		pipe->pipetrn = get_pipetrn_addr(pipenum);
	} else {
		pipe->pipetre = 0;
		pipe->pipetrn = 0;
	}
}