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
struct tracepoint {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct tracepoint* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tracepoint*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct tracepoint* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tracepoint *alloc_synth_tracepoint(char *name)
{
	struct tracepoint *tp;

	tp = kzalloc(sizeof(*tp), GFP_KERNEL);
	if (!tp)
		return ERR_PTR(-ENOMEM);

	tp->name = kstrdup(name, GFP_KERNEL);
	if (!tp->name) {
		kfree(tp);
		return ERR_PTR(-ENOMEM);
	}

	return tp;
}