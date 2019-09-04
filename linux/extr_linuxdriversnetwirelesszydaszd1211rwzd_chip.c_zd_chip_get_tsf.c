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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int u64 ;
typedef  int u32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CR_TSF_HIGH_PART 129 
#define  CR_TSF_LOW_PART 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zd_ioread32v_locked (struct zd_chip*,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

u64 zd_chip_get_tsf(struct zd_chip *chip)
{
	int r;
	static const zd_addr_t aw_pt_bi_addr[] =
		{ CR_TSF_LOW_PART, CR_TSF_HIGH_PART };
	u32 values[2];
	u64 tsf;

	mutex_lock(&chip->mutex);
	r = zd_ioread32v_locked(chip, values, (const zd_addr_t *)aw_pt_bi_addr,
	                        ARRAY_SIZE(aw_pt_bi_addr));
	mutex_unlock(&chip->mutex);
	if (r)
		return 0;

	tsf = values[1];
	tsf = (tsf << 32) | values[0];

	return tsf;
}