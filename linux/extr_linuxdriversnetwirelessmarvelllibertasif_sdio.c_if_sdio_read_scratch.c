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
struct if_sdio_card {scalar_t__ scratch_reg; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int sdio_readb (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static u16 if_sdio_read_scratch(struct if_sdio_card *card, int *err)
{
	int ret;
	u16 scratch;

	scratch = sdio_readb(card->func, card->scratch_reg, &ret);
	if (!ret)
		scratch |= sdio_readb(card->func, card->scratch_reg + 1,
					&ret) << 8;

	if (err)
		*err = ret;

	if (ret)
		return 0xffff;

	return scratch;
}