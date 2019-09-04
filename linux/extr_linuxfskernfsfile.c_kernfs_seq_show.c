#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct kernfs_open_file* private; } ;
struct kernfs_open_file {TYPE_4__* kn; int /*<<< orphan*/  event; } ;
struct TYPE_7__ {TYPE_2__* ops; TYPE_1__* open; } ;
struct TYPE_8__ {TYPE_3__ attr; } ;
struct TYPE_6__ {int (* seq_show ) (struct seq_file*,void*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct seq_file*,void*) ; 

__attribute__((used)) static int kernfs_seq_show(struct seq_file *sf, void *v)
{
	struct kernfs_open_file *of = sf->private;

	of->event = atomic_read(&of->kn->attr.open->event);

	return of->kn->attr.ops->seq_show(sf, v);
}