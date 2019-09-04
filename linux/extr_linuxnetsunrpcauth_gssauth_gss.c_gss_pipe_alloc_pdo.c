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
struct rpc_pipe_dir_object {int dummy; } ;
struct gss_pipe {struct rpc_pipe_dir_object pdo; } ;
struct gss_alloc_pdo {int /*<<< orphan*/  upcall_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  clnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct gss_pipe*) ; 
 struct gss_pipe* gss_pipe_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_pipe_dir_object *gss_pipe_alloc_pdo(void *data)
{
	struct gss_pipe *gss_pipe;
	struct gss_alloc_pdo *args = data;

	gss_pipe = gss_pipe_alloc(args->clnt, args->name, args->upcall_ops);
	if (!IS_ERR(gss_pipe))
		return &gss_pipe->pdo;
	return NULL;
}