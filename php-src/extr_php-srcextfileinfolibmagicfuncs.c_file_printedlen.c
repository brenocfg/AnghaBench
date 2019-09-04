#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;
struct magic_set {TYPE_1__ o; } ;

/* Variables and functions */
 size_t strlen (int /*<<< orphan*/ *) ; 

size_t
file_printedlen(const struct magic_set *ms)
{
	return ms->o.buf == NULL ? 0 : strlen(ms->o.buf);
}