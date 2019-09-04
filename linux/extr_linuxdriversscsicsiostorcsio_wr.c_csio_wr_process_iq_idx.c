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
struct csio_wrm {struct csio_q** q_arr; } ;
struct csio_q {int dummy; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int csio_wr_process_iq (struct csio_hw*,struct csio_q*,void (*) (struct csio_hw*,void*,uint32_t,struct csio_fl_dma_buf*,void*),void*) ; 

int
csio_wr_process_iq_idx(struct csio_hw *hw, int qidx,
		   void (*iq_handler)(struct csio_hw *, void *,
				      uint32_t, struct csio_fl_dma_buf *,
				      void *),
		   void *priv)
{
	struct csio_wrm *wrm	= csio_hw_to_wrm(hw);
	struct csio_q	*iq	= wrm->q_arr[qidx];

	return csio_wr_process_iq(hw, iq, iq_handler, priv);
}