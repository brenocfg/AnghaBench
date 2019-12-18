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
struct cflayer {int dummy; } ;
struct cffrml {int /*<<< orphan*/  pcpu_refcnt; } ;

/* Variables and functions */
 struct cffrml* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cflayer*) ; 

void cffrml_free(struct cflayer *layer)
{
	struct cffrml *this = container_obj(layer);
	free_percpu(this->pcpu_refcnt);
	kfree(layer);
}