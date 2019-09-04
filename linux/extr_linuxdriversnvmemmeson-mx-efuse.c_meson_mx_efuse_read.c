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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int word_size; } ;
struct meson_mx_efuse {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1 ; 
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  meson_mx_efuse_hw_disable (struct meson_mx_efuse*) ; 
 int meson_mx_efuse_hw_enable (struct meson_mx_efuse*) ; 
 int /*<<< orphan*/  meson_mx_efuse_mask_bits (struct meson_mx_efuse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int meson_mx_efuse_read_addr (struct meson_mx_efuse*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_mx_efuse_read(void *context, unsigned int offset,
			       void *buf, size_t bytes)
{
	struct meson_mx_efuse *efuse = context;
	u32 tmp;
	int err, i, addr;

	err = meson_mx_efuse_hw_enable(efuse);
	if (err)
		return err;

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE);

	for (i = 0; i < bytes; i += efuse->config.word_size) {
		addr = (offset + i) / efuse->config.word_size;

		err = meson_mx_efuse_read_addr(efuse, addr, &tmp);
		if (err)
			break;

		memcpy(buf + i, &tmp, efuse->config.word_size);
	}

	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_AUTO_RD_ENABLE, 0);

	meson_mx_efuse_hw_disable(efuse);

	return err;
}