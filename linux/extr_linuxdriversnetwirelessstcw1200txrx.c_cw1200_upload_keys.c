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
struct cw1200_common {int key_map; int /*<<< orphan*/ * keys; } ;

/* Variables and functions */
 int BIT (int) ; 
 int WSM_KEY_MAX_INDEX ; 
 int wsm_add_key (struct cw1200_common*,int /*<<< orphan*/ *) ; 

int cw1200_upload_keys(struct cw1200_common *priv)
{
	int idx, ret = 0;
	for (idx = 0; idx <= WSM_KEY_MAX_INDEX; ++idx)
		if (priv->key_map & BIT(idx)) {
			ret = wsm_add_key(priv, &priv->keys[idx]);
			if (ret < 0)
				break;
		}
	return ret;
}