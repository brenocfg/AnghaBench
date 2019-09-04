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
struct ulptx_idata {void* len; void* cmd_more; } ;
struct TYPE_2__ {void* wr_hi; } ;
struct ulp_mem_io {void* len16; void* lock_addr; void* dlen; void* cmd; TYPE_1__ wr; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {int /*<<< orphan*/  adapter_type; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  FW_ULPTX_WR ; 
 unsigned int FW_WR_ATOMIC_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_ULPTX_WR (struct ulp_mem_io*,unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned int T5_ULP_MEMIO_IMM_V (int) ; 
 unsigned int ULPTX_CMD_V (int /*<<< orphan*/ ) ; 
 unsigned int ULP_MEMIO_ADDR_V (unsigned int) ; 
 unsigned int ULP_MEMIO_DATA_LEN_V (unsigned int) ; 
 unsigned int ULP_MEMIO_ORDER_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULP_TX_MEM_WRITE ; 
 int /*<<< orphan*/  ULP_TX_SC_IMM ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (struct cxgbi_device*) ; 
 void* htonl (unsigned int) ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ulp_mem_io_set_hdr(struct cxgbi_device *cdev,
		   struct ulp_mem_io *req,
		   unsigned int wr_len, unsigned int dlen,
		   unsigned int pm_addr,
		   int tid)
{
	struct cxgb4_lld_info *lldi = cxgbi_cdev_priv(cdev);
	struct ulptx_idata *idata = (struct ulptx_idata *)(req + 1);

	INIT_ULPTX_WR(req, wr_len, 0, tid);
	req->wr.wr_hi = htonl(FW_WR_OP_V(FW_ULPTX_WR) |
		FW_WR_ATOMIC_V(0));
	req->cmd = htonl(ULPTX_CMD_V(ULP_TX_MEM_WRITE) |
		ULP_MEMIO_ORDER_V(is_t4(lldi->adapter_type)) |
		T5_ULP_MEMIO_IMM_V(!is_t4(lldi->adapter_type)));
	req->dlen = htonl(ULP_MEMIO_DATA_LEN_V(dlen >> 5));
	req->lock_addr = htonl(ULP_MEMIO_ADDR_V(pm_addr >> 5));
	req->len16 = htonl(DIV_ROUND_UP(wr_len - sizeof(req->wr), 16));

	idata->cmd_more = htonl(ULPTX_CMD_V(ULP_TX_SC_IMM));
	idata->len = htonl(dlen);
}