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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_CXGBIT ; 
 int /*<<< orphan*/  lio_target_np_driver_store (struct config_item*,char const*,size_t,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t lio_target_np_cxgbit_store(struct config_item *item,
					  const char *page, size_t count)
{
	return lio_target_np_driver_store(item, page, count,
					  ISCSI_CXGBIT, "cxgbit");
}