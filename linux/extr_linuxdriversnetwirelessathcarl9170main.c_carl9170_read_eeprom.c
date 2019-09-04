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
struct ar9170 {int /*<<< orphan*/  eeprom; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ AR9170_EEPROM_START ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CARL9170_CMD_RREG ; 
 int CARL9170_MAX_CMD_LEN ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static int carl9170_read_eeprom(struct ar9170 *ar)
{
#define RW	8	/* number of words to read at once */
#define RB	(sizeof(u32) * RW)
	u8 *eeprom = (void *)&ar->eeprom;
	__le32 offsets[RW];
	int i, j, err;

	BUILD_BUG_ON(sizeof(ar->eeprom) & 3);

	BUILD_BUG_ON(RB > CARL9170_MAX_CMD_LEN - 4);
#ifndef __CHECKER__
	/* don't want to handle trailing remains */
	BUILD_BUG_ON(sizeof(ar->eeprom) % RB);
#endif

	for (i = 0; i < sizeof(ar->eeprom) / RB; i++) {
		for (j = 0; j < RW; j++)
			offsets[j] = cpu_to_le32(AR9170_EEPROM_START +
						 RB * i + 4 * j);

		err = carl9170_exec_cmd(ar, CARL9170_CMD_RREG,
					RB, (u8 *) &offsets,
					RB, eeprom + RB * i);
		if (err)
			return err;
	}

#undef RW
#undef RB
	return 0;
}