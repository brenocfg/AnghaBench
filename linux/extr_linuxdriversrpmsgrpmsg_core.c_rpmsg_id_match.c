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
struct rpmsg_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rpmsg_id_match(const struct rpmsg_device *rpdev,
				  const struct rpmsg_device_id *id)
{
	return strncmp(id->name, rpdev->id.name, RPMSG_NAME_SIZE) == 0;
}