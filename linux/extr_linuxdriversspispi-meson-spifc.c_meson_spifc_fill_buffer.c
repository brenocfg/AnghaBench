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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct meson_spifc {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ REG_C0 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_spifc_fill_buffer(struct meson_spifc *spifc, const u8 *buf,
				    int len)
{
	u32 data;
	int i = 0;

	while (i < len) {
		if (len - i >= 4)
			data = *(u32 *)buf;
		else
			memcpy(&data, buf, len - i);

		regmap_write(spifc->regmap, REG_C0 + i, data);

		buf += 4;
		i += 4;
	}
}