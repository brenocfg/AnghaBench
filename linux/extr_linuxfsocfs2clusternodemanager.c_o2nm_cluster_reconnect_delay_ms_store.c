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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  cl_reconnect_delay_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2nm_cluster_attr_write (char const*,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_o2nm_cluster (struct config_item*) ; 

__attribute__((used)) static ssize_t o2nm_cluster_reconnect_delay_ms_store(
	struct config_item *item, const char *page, size_t count)
{
	return o2nm_cluster_attr_write(page, count,
                               &to_o2nm_cluster(item)->cl_reconnect_delay_ms);
}