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
typedef  int /*<<< orphan*/  uint8_t ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int udf_name_from_CS0 (struct super_block*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int) ; 

int udf_get_filename(struct super_block *sb, const uint8_t *sname, int slen,
		     uint8_t *dname, int dlen)
{
	int ret;

	if (!slen)
		return -EIO;

	if (dlen <= 0)
		return 0;

	ret = udf_name_from_CS0(sb, dname, dlen, sname, slen, 1);
	/* Zero length filename isn't valid... */
	if (ret == 0)
		ret = -EINVAL;
	return ret;
}