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
typedef  int /*<<< orphan*/  u8 ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int aac_sa_restart_adapter(struct aac_dev *dev, int bled, u8 reset_type)
{
	return -EINVAL;
}