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
typedef  int u8 ;
typedef  size_t u32 ;
struct mwifiex_private {int data_rate; int /*<<< orphan*/  adapter; int /*<<< orphan*/  is_data_rate_auto; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmemdup (int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int mwifiex_get_common_rates(struct mwifiex_private *priv, u8 *rate1,
				    u32 rate1_size, u8 *rate2, u32 rate2_size)
{
	int ret;
	u8 *ptr = rate1, *tmp;
	u32 i, j;

	tmp = kmemdup(rate1, rate1_size, GFP_KERNEL);
	if (!tmp) {
		mwifiex_dbg(priv->adapter, ERROR, "failed to alloc tmp buf\n");
		return -ENOMEM;
	}

	memset(rate1, 0, rate1_size);

	for (i = 0; i < rate2_size && rate2[i]; i++) {
		for (j = 0; j < rate1_size && tmp[j]; j++) {
			/* Check common rate, excluding the bit for
			   basic rate */
			if ((rate2[i] & 0x7F) == (tmp[j] & 0x7F)) {
				*rate1++ = tmp[j];
				break;
			}
		}
	}

	mwifiex_dbg(priv->adapter, INFO, "info: Tx data rate set to %#x\n",
		    priv->data_rate);

	if (!priv->is_data_rate_auto) {
		while (*ptr) {
			if ((*ptr & 0x7f) == priv->data_rate) {
				ret = 0;
				goto done;
			}
			ptr++;
		}
		mwifiex_dbg(priv->adapter, ERROR,
			    "previously set fixed data rate %#x\t"
			    "is not compatible with the network\n",
			    priv->data_rate);

		ret = -1;
		goto done;
	}

	ret = 0;
done:
	kfree(tmp);
	return ret;
}