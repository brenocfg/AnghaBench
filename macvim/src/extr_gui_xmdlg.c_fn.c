#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; char** names; } ;
typedef  TYPE_1__ SharedFontSelData ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static char *
fn(SharedFontSelData *data, int i)
{
    /* Assertion checks: */
    if (data->num < 0)
	abort();
    if (i >= data->num)
	i = data->num - 1;
    if (i < 0)
	i = 0;

    return data->names[i];
}