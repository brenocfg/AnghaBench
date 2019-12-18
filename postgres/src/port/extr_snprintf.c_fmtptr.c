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
struct TYPE_4__ {int failed; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 int /*<<< orphan*/  dostr (char*,int,TYPE_1__*) ; 
 int sprintf (char*,char*,void*) ; 

__attribute__((used)) static void
fmtptr(void *value, PrintfTarget *target)
{
	int			vallen;
	char		convert[64];

	/* we rely on regular C library's sprintf to do the basic conversion */
	vallen = sprintf(convert, "%p", value);
	if (vallen < 0)
		target->failed = true;
	else
		dostr(convert, vallen, target);
}