#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fns {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;} ;
struct TYPE_4__ {scalar_t__ re_fns; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
pg_regfree(regex_t *re)
{
	if (re == NULL)
		return;
	(*((struct fns *) re->re_fns)->free) (re);
}