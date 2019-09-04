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
struct ks_wlan_private {int dummy; } ;
typedef  int /*<<< orphan*/  index ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  READ_INDEX_REG ; 
 int /*<<< orphan*/  WRITE_INDEX_REG ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ks7010_sdio_write (struct ks_wlan_private*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ks7010_sdio_update_index(struct ks_wlan_private *priv, u32 index)
{
	int ret;
	unsigned char *data_buf;

	data_buf = kmemdup(&index, sizeof(u32), GFP_KERNEL);
	if (!data_buf)
		return -ENOMEM;

	ret = ks7010_sdio_write(priv, WRITE_INDEX_REG, data_buf, sizeof(index));
	if (ret)
		goto err_free_data_buf;

	ret = ks7010_sdio_write(priv, READ_INDEX_REG, data_buf, sizeof(index));
	if (ret)
		goto err_free_data_buf;

	return 0;

err_free_data_buf:
	kfree(data_buf);

	return ret;
}