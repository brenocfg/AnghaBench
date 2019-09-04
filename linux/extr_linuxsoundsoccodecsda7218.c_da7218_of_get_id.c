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
struct of_device_id {int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  da7218_of_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static inline int da7218_of_get_id(struct device *dev)
{
	const struct of_device_id *id = of_match_device(da7218_of_match, dev);

	if (id)
		return (uintptr_t)id->data;
	else
		return -EINVAL;
}