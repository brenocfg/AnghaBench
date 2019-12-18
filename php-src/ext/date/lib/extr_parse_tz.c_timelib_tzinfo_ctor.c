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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ timelib_tzinfo ;

/* Variables and functions */
 TYPE_1__* timelib_calloc (int,int) ; 
 int /*<<< orphan*/  timelib_strdup (char*) ; 

__attribute__((used)) static timelib_tzinfo* timelib_tzinfo_ctor(char *name)
{
	timelib_tzinfo *t;
	t = timelib_calloc(1, sizeof(timelib_tzinfo));
	t->name = timelib_strdup(name);

	return t;
}