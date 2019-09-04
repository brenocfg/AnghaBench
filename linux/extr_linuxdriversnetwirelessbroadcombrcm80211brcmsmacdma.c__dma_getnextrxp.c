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
struct sk_buff {int dummy; } ;
struct dma_info {scalar_t__ nrxd; } ;

/* Variables and functions */
 struct sk_buff* dma64_getnextrxp (struct dma_info*,int) ; 

__attribute__((used)) static struct sk_buff *_dma_getnextrxp(struct dma_info *di, bool forceall)
{
	if (di->nrxd == 0)
		return NULL;

	return dma64_getnextrxp(di, forceall);
}