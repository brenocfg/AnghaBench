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
typedef  int u16 ;
struct isp1362_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCDIRADDR ; 
 int HCDIRADDR_ADDR (int) ; 
 int HCDIRADDR_COUNT (int) ; 
 int /*<<< orphan*/  HCDMACFG ; 
 int /*<<< orphan*/  HCDMACFG_CTR_ENABLE ; 
 int /*<<< orphan*/  isp1362_clr_mask16 (struct isp1362_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1362_write_reg32 (struct isp1362_hcd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isp1362_write_diraddr(struct isp1362_hcd *isp1362_hcd, u16 offset, u16 len)
{
	len = (len + 1) & ~1;

	isp1362_clr_mask16(isp1362_hcd, HCDMACFG, HCDMACFG_CTR_ENABLE);
	isp1362_write_reg32(isp1362_hcd, HCDIRADDR,
			    HCDIRADDR_ADDR(offset) | HCDIRADDR_COUNT(len));
}