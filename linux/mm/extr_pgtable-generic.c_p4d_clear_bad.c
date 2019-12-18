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
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  p4d_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4d_clear (int /*<<< orphan*/ *) ; 

void p4d_clear_bad(p4d_t *p4d)
{
	p4d_ERROR(*p4d);
	p4d_clear(p4d);
}