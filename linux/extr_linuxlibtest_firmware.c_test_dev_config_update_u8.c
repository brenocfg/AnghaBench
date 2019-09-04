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
typedef  long u8 ;

/* Variables and functions */
 int EINVAL ; 
 long U8_MAX ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_fw_mutex ; 

__attribute__((used)) static int test_dev_config_update_u8(const char *buf, size_t size, u8 *cfg)
{
	int ret;
	long new;

	ret = kstrtol(buf, 10, &new);
	if (ret)
		return ret;

	if (new > U8_MAX)
		return -EINVAL;

	mutex_lock(&test_fw_mutex);
	*(u8 *)cfg = new;
	mutex_unlock(&test_fw_mutex);

	/* Always return full write size even if we didn't consume all */
	return size;
}