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
struct call_return_processor {int (* process ) (struct call_return*,void*) ;void* data; int /*<<< orphan*/  cpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_path_root__new () ; 
 int /*<<< orphan*/  free (struct call_return_processor*) ; 
 struct call_return_processor* zalloc (int) ; 

struct call_return_processor *
call_return_processor__new(int (*process)(struct call_return *cr, void *data),
			   void *data)
{
	struct call_return_processor *crp;

	crp = zalloc(sizeof(struct call_return_processor));
	if (!crp)
		return NULL;
	crp->cpr = call_path_root__new();
	if (!crp->cpr)
		goto out_free;
	crp->process = process;
	crp->data = data;
	return crp;

out_free:
	free(crp);
	return NULL;
}