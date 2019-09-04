#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bytes_global; } ;
struct TYPE_5__ {struct TYPE_5__* data; TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  deinit_thread_data () ; 
 int /*<<< orphan*/  free_data (TYPE_2__*,int) ; 
 TYPE_2__* g ; 

__attribute__((used)) static void deinit(void)
{
	free_data(g->data, g->p.bytes_global);
	g->data = NULL;

	deinit_thread_data();

	free_data(g, sizeof(*g));
	g = NULL;
}