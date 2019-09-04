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
struct vc_sm_privdata_t {int pid; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  alloc_name ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vc_sm_privdata_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static struct vc_sm_privdata_t *vc_sm_cma_create_priv_data(pid_t id)
{
	char alloc_name[32];
	struct vc_sm_privdata_t *file_data = NULL;

	/* Allocate private structure. */
	file_data = kzalloc(sizeof(*file_data), GFP_KERNEL);

	if (!file_data)
		return NULL;

	snprintf(alloc_name, sizeof(alloc_name), "%d", id);

	file_data->pid = id;

	return file_data;
}