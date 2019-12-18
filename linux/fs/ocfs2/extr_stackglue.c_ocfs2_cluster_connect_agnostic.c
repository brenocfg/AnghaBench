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
struct ocfs2_locking_protocol {int dummy; } ;
struct ocfs2_cluster_connection {int dummy; } ;

/* Variables and functions */
 char* cluster_stack_name ; 
 int ocfs2_cluster_connect (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,struct ocfs2_locking_protocol*,void (*) (int,void*),void*,struct ocfs2_cluster_connection**) ; 

int ocfs2_cluster_connect_agnostic(const char *group,
				   int grouplen,
				   struct ocfs2_locking_protocol *lproto,
				   void (*recovery_handler)(int node_num,
							    void *recovery_data),
				   void *recovery_data,
				   struct ocfs2_cluster_connection **conn)
{
	char *stack_name = NULL;

	if (cluster_stack_name[0])
		stack_name = cluster_stack_name;
	return ocfs2_cluster_connect(stack_name, NULL, 0, group, grouplen,
				     lproto, recovery_handler, recovery_data,
				     conn);
}