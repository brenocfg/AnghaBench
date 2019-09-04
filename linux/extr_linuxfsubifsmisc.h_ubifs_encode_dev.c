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
union ubifs_dev_desc {int /*<<< orphan*/  new; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ubifs_encode_dev(union ubifs_dev_desc *dev, dev_t rdev)
{
	dev->new = cpu_to_le32(new_encode_dev(rdev));
	return sizeof(dev->new);
}