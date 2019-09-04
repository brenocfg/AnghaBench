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
struct zd_ioreq32 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq32 const*) ; 
#define  CR_RX_THRESHOLD 137 
#define  CR_ZD1211B_AIFS_CTL1 136 
#define  CR_ZD1211B_AIFS_CTL2 135 
#define  CR_ZD1211B_CWIN_MAX_MIN_AC0 134 
#define  CR_ZD1211B_CWIN_MAX_MIN_AC1 133 
#define  CR_ZD1211B_CWIN_MAX_MIN_AC2 132 
#define  CR_ZD1211B_CWIN_MAX_MIN_AC3 131 
#define  CR_ZD1211B_RETRY_MAX 130 
#define  CR_ZD1211B_TXOP 129 
#define  ZD1211B_RETRY_COUNT 128 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_iowrite32a_locked (struct zd_chip*,struct zd_ioreq32 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211b_hw_init_hmac(struct zd_chip *chip)
{
	static const struct zd_ioreq32 ioreqs[] = {
		{ CR_ZD1211B_RETRY_MAX,		ZD1211B_RETRY_COUNT },
		{ CR_ZD1211B_CWIN_MAX_MIN_AC0,	0x007f003f },
		{ CR_ZD1211B_CWIN_MAX_MIN_AC1,	0x007f003f },
		{ CR_ZD1211B_CWIN_MAX_MIN_AC2,  0x003f001f },
		{ CR_ZD1211B_CWIN_MAX_MIN_AC3,  0x001f000f },
		{ CR_ZD1211B_AIFS_CTL1,		0x00280028 },
		{ CR_ZD1211B_AIFS_CTL2,		0x008C003C },
		{ CR_ZD1211B_TXOP,		0x01800824 },
		{ CR_RX_THRESHOLD,		0x000c0eff, },
	};

	dev_dbg_f(zd_chip_dev(chip), "\n");
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	return zd_iowrite32a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}