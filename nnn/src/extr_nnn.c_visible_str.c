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
struct TYPE_3__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ fltrexp_t ;

/* Variables and functions */
 int /*<<< orphan*/ * strcasestr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visible_str(const fltrexp_t *fltrexp, const char *fname)
{
	return strcasestr(fname, fltrexp->str) != NULL;
}