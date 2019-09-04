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
typedef  int u32 ;
typedef  short u16 ;
struct stm32_spdifrx_data {unsigned char* cs; int /*<<< orphan*/  cs_completion; TYPE_1__* dmab; int /*<<< orphan*/  regmap; scalar_t__ ub; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ area; } ;

/* Variables and functions */
 scalar_t__ SPDIFRX_CR_CBDMAEN ; 
 scalar_t__ SPDIFRX_CSR_CSGET (int) ; 
 int SPDIFRX_CSR_SOB ; 
 int /*<<< orphan*/  SPDIFRX_CSR_USRGET (int /*<<< orphan*/ ) ; 
 int SPDIFRX_CS_BYTES_NB ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static void stm32_spdifrx_dma_complete(void *data)
{
	struct stm32_spdifrx_data *spdifrx = (struct stm32_spdifrx_data *)data;
	struct platform_device *pdev = spdifrx->pdev;
	u32 *p_start = (u32 *)spdifrx->dmab->area;
	u32 *p_end = p_start + (2 * SPDIFRX_CS_BYTES_NB) - 1;
	u32 *ptr = p_start;
	u16 *ub_ptr = (short *)spdifrx->ub;
	int i = 0;

	regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR,
			   SPDIFRX_CR_CBDMAEN,
			   (unsigned int)~SPDIFRX_CR_CBDMAEN);

	if (!spdifrx->dmab->area)
		return;

	while (ptr <= p_end) {
		if (*ptr & SPDIFRX_CSR_SOB)
			break;
		ptr++;
	}

	if (ptr > p_end) {
		dev_err(&pdev->dev, "Start of S/PDIF block not found\n");
		return;
	}

	while (i < SPDIFRX_CS_BYTES_NB) {
		spdifrx->cs[i] = (unsigned char)SPDIFRX_CSR_CSGET(*ptr);
		*ub_ptr++ = SPDIFRX_CSR_USRGET(*ptr++);
		if (ptr > p_end) {
			dev_err(&pdev->dev, "Failed to get channel status\n");
			return;
		}
		i++;
	}

	complete(&spdifrx->cs_completion);
}