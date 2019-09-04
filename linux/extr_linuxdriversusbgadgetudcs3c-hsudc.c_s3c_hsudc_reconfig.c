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
struct s3c_hsudc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C_EDR ; 
 scalar_t__ S3C_EIER ; 
 scalar_t__ S3C_EP0CR ; 
 scalar_t__ S3C_SCR ; 
 int S3C_SCR_DTZIEN_EN ; 
 int S3C_SCR_RRD_EN ; 
 int S3C_SCR_RST_EN ; 
 int S3C_SCR_SUS_EN ; 
 scalar_t__ S3C_TR ; 
 int /*<<< orphan*/  s3c_hsudc_setup_ep (struct s3c_hsudc*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c_hsudc_reconfig(struct s3c_hsudc *hsudc)
{
	writel(0xAA, hsudc->regs + S3C_EDR);
	writel(1, hsudc->regs + S3C_EIER);
	writel(0, hsudc->regs + S3C_TR);
	writel(S3C_SCR_DTZIEN_EN | S3C_SCR_RRD_EN | S3C_SCR_SUS_EN |
			S3C_SCR_RST_EN, hsudc->regs + S3C_SCR);
	writel(0, hsudc->regs + S3C_EP0CR);

	s3c_hsudc_setup_ep(hsudc);
}