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
typedef  scalar_t__ u16 ;
struct s3c_hsudc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C_BR (int /*<<< orphan*/ ) ; 
 scalar_t__ S3C_BRCR ; 
 scalar_t__ S3C_EP0SR ; 
 int /*<<< orphan*/  S3C_EP0SR_RX_SUCCESS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s3c_hsudc_read_setup_pkt(struct s3c_hsudc *hsudc, u16 *buf)
{
	int count;

	count = readl(hsudc->regs + S3C_BRCR);
	while (count--)
		*buf++ = (u16)readl(hsudc->regs + S3C_BR(0));

	writel(S3C_EP0SR_RX_SUCCESS, hsudc->regs + S3C_EP0SR);
}