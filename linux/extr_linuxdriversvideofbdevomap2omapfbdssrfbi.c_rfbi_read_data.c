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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int parallelmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  OMAP_DSS_RFBI_PARALLELMODE_12 131 
#define  OMAP_DSS_RFBI_PARALLELMODE_16 130 
#define  OMAP_DSS_RFBI_PARALLELMODE_8 129 
#define  OMAP_DSS_RFBI_PARALLELMODE_9 128 
 int /*<<< orphan*/  RFBI_READ ; 
 TYPE_1__ rfbi ; 
 void* rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfbi_read_data(void *buf, u32 len)
{
	switch (rfbi.parallelmode) {
	case OMAP_DSS_RFBI_PARALLELMODE_8:
	{
		u8 *b = buf;
		for (; len; len--) {
			rfbi_write_reg(RFBI_READ, 0);
			*b++ = rfbi_read_reg(RFBI_READ);
		}
		break;
	}

	case OMAP_DSS_RFBI_PARALLELMODE_16:
	{
		u16 *w = buf;
		BUG_ON(len & ~1);
		for (; len; len -= 2) {
			rfbi_write_reg(RFBI_READ, 0);
			*w++ = rfbi_read_reg(RFBI_READ);
		}
		break;
	}

	case OMAP_DSS_RFBI_PARALLELMODE_9:
	case OMAP_DSS_RFBI_PARALLELMODE_12:
	default:
		BUG();
	}
}