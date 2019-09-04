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
struct ms_info {int /*<<< orphan*/  err_code; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */

__attribute__((used)) static inline void ms_set_err_code(struct rtsx_chip *chip, u8 err_code)
{
	struct ms_info *ms_card = &chip->ms_card;

	ms_card->err_code = err_code;
}