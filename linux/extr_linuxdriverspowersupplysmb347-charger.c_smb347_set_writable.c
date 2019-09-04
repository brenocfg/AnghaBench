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
struct smb347_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_A ; 
 int /*<<< orphan*/  CMD_A_ALLOW_WRITE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smb347_set_writable(struct smb347_charger *smb, bool writable)
{
	return regmap_update_bits(smb->regmap, CMD_A, CMD_A_ALLOW_WRITE,
				  writable ? CMD_A_ALLOW_WRITE : 0);
}