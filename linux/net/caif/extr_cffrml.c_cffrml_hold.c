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
struct cffrml {int /*<<< orphan*/ * pcpu_refcnt; } ;

/* Variables and functions */
 struct cffrml* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

void cffrml_hold(struct cflayer *layr)
{
	struct cffrml *this = container_obj(layr);
	if (layr != NULL && this->pcpu_refcnt != NULL)
		this_cpu_inc(*this->pcpu_refcnt);
}