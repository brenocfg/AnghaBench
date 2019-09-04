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
typedef  char u8 ;
typedef  int u32 ;
struct wsm_buf {char* begin; char* data; char* end; } ;
struct cw1200_common {TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  WSM_GET (struct wsm_buf*,char*,int) ; 
 int WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,...) ; 

int wsm_handle_exception(struct cw1200_common *priv, u8 *data, size_t len)
{
	struct wsm_buf buf;
	u32 reason;
	u32 reg[18];
	char fname[48];
	unsigned int i;

	static const char * const reason_str[] = {
		"undefined instruction",
		"prefetch abort",
		"data abort",
		"unknown error",
	};

	buf.begin = buf.data = data;
	buf.end = &buf.begin[len];

	reason = WSM_GET32(&buf);
	for (i = 0; i < ARRAY_SIZE(reg); ++i)
		reg[i] = WSM_GET32(&buf);
	WSM_GET(&buf, fname, sizeof(fname));

	if (reason < 4)
		wiphy_err(priv->hw->wiphy,
			  "Firmware exception: %s.\n",
			  reason_str[reason]);
	else
		wiphy_err(priv->hw->wiphy,
			  "Firmware assert at %.*s, line %d\n",
			  (int) sizeof(fname), fname, reg[1]);

	for (i = 0; i < 12; i += 4)
		wiphy_err(priv->hw->wiphy,
			  "R%d: 0x%.8X, R%d: 0x%.8X, R%d: 0x%.8X, R%d: 0x%.8X,\n",
			  i + 0, reg[i + 0], i + 1, reg[i + 1],
			  i + 2, reg[i + 2], i + 3, reg[i + 3]);
	wiphy_err(priv->hw->wiphy,
		  "R12: 0x%.8X, SP: 0x%.8X, LR: 0x%.8X, PC: 0x%.8X,\n",
		  reg[i + 0], reg[i + 1], reg[i + 2], reg[i + 3]);
	i += 4;
	wiphy_err(priv->hw->wiphy,
		  "CPSR: 0x%.8X, SPSR: 0x%.8X\n",
		  reg[i + 0], reg[i + 1]);

	print_hex_dump_bytes("R1: ", DUMP_PREFIX_NONE,
			     fname, sizeof(fname));
	return 0;

underflow:
	wiphy_err(priv->hw->wiphy, "Firmware exception.\n");
	print_hex_dump_bytes("Exception: ", DUMP_PREFIX_NONE,
			     data, len);
	return -EINVAL;
}