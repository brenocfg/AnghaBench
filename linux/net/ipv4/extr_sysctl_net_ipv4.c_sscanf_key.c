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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sscanf_key(char *buf, __le32 *key)
{
	u32 user_key[4];
	int i, ret = 0;

	if (sscanf(buf, "%x-%x-%x-%x", user_key, user_key + 1,
		   user_key + 2, user_key + 3) != 4) {
		ret = -EINVAL;
	} else {
		for (i = 0; i < ARRAY_SIZE(user_key); i++)
			key[i] = cpu_to_le32(user_key[i]);
	}
	pr_debug("proc TFO key set 0x%x-%x-%x-%x <- 0x%s: %u\n",
		 user_key[0], user_key[1], user_key[2], user_key[3], buf, ret);

	return ret;
}