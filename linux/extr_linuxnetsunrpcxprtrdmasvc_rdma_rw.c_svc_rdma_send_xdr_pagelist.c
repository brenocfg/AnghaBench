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
struct xdr_buf {int /*<<< orphan*/  page_len; } ;
struct svc_rdma_write_info {scalar_t__ wi_next_off; struct xdr_buf* wi_xdr; } ;

/* Variables and functions */
 int svc_rdma_build_writes (struct svc_rdma_write_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_pagelist_to_sg ; 

__attribute__((used)) static int svc_rdma_send_xdr_pagelist(struct svc_rdma_write_info *info,
				      struct xdr_buf *xdr)
{
	info->wi_xdr = xdr;
	info->wi_next_off = 0;
	return svc_rdma_build_writes(info, svc_rdma_pagelist_to_sg,
				     xdr->page_len);
}