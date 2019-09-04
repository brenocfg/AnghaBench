#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cw1200_common {TYPE_1__* keys; int /*<<< orphan*/  key_map; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int WSM_KEY_MAX_INDEX ; 
 int ffs (int /*<<< orphan*/ ) ; 

int cw1200_alloc_key(struct cw1200_common *priv)
{
	int idx;

	idx = ffs(~priv->key_map) - 1;
	if (idx < 0 || idx > WSM_KEY_MAX_INDEX)
		return -1;

	priv->key_map |= BIT(idx);
	priv->keys[idx].index = idx;
	return idx;
}