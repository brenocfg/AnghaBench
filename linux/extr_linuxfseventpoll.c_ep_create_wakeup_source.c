#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wakeup_source {int dummy; } ;
struct TYPE_8__ {TYPE_1__* file; } ;
struct epitem {int /*<<< orphan*/  ws; TYPE_2__ ffd; TYPE_3__* ep; } ;
struct TYPE_12__ {TYPE_4__* dentry; } ;
struct TYPE_11__ {char* name; } ;
struct TYPE_10__ {TYPE_5__ d_name; } ;
struct TYPE_9__ {void* ws; } ;
struct TYPE_7__ {TYPE_6__ f_path; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct wakeup_source*) ; 
 void* wakeup_source_register (char const*) ; 

__attribute__((used)) static int ep_create_wakeup_source(struct epitem *epi)
{
	const char *name;
	struct wakeup_source *ws;

	if (!epi->ep->ws) {
		epi->ep->ws = wakeup_source_register("eventpoll");
		if (!epi->ep->ws)
			return -ENOMEM;
	}

	name = epi->ffd.file->f_path.dentry->d_name.name;
	ws = wakeup_source_register(name);

	if (!ws)
		return -ENOMEM;
	rcu_assign_pointer(epi->ws, ws);

	return 0;
}