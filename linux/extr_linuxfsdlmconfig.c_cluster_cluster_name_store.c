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
struct dlm_cluster {int /*<<< orphan*/  cl_cluster_name; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  ci_cluster_name; } ;

/* Variables and functions */
 struct dlm_cluster* config_item_to_cluster (struct config_item*) ; 
 TYPE_1__ dlm_config ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static ssize_t cluster_cluster_name_store(struct config_item *item,
					  const char *buf, size_t len)
{
	struct dlm_cluster *cl = config_item_to_cluster(item);

	strlcpy(dlm_config.ci_cluster_name, buf,
				sizeof(dlm_config.ci_cluster_name));
	strlcpy(cl->cl_cluster_name, buf, sizeof(cl->cl_cluster_name));
	return len;
}