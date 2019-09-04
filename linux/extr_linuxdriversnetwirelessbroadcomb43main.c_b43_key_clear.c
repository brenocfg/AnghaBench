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
struct b43_wldev {TYPE_1__* key; } ;
struct TYPE_2__ {int /*<<< orphan*/ * keyconf; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  B43_SEC_ALGO_NONE ; 
 int /*<<< orphan*/  B43_SEC_KEYSIZE ; 
 scalar_t__ B43_WARN_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  b43_new_kidx_api (struct b43_wldev*) ; 
 int /*<<< orphan*/  do_key_write (struct b43_wldev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b43_key_clear(struct b43_wldev *dev, int index)
{
	if (B43_WARN_ON((index < 0) || (index >= ARRAY_SIZE(dev->key))))
		return -EINVAL;
	do_key_write(dev, index, B43_SEC_ALGO_NONE,
		     NULL, B43_SEC_KEYSIZE, NULL);
	if ((index <= 3) && !b43_new_kidx_api(dev)) {
		do_key_write(dev, index + 4, B43_SEC_ALGO_NONE,
			     NULL, B43_SEC_KEYSIZE, NULL);
	}
	dev->key[index].keyconf = NULL;

	return 0;
}