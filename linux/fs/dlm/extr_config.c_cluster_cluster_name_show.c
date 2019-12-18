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
struct dlm_cluster {char* cl_cluster_name; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct dlm_cluster* config_item_to_cluster (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t cluster_cluster_name_show(struct config_item *item, char *buf)
{
	struct dlm_cluster *cl = config_item_to_cluster(item);
	return sprintf(buf, "%s\n", cl->cl_cluster_name);
}