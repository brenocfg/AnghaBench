#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  msg_received; } ;
struct TYPE_4__ {TYPE_1__ lcp; } ;
struct c67x00_device {TYPE_2__ hpi; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int ll_recv_msg(struct c67x00_device *dev)
{
	u16 res;

	res = wait_for_completion_timeout(&dev->hpi.lcp.msg_received, 5 * HZ);
	WARN_ON(!res);

	return (res == 0) ? -EIO : 0;
}