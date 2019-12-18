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
struct TYPE_2__ {int c; } ;
typedef  TYPE_1__ spgNodePtr ;

/* Variables and functions */

__attribute__((used)) static int
cmpNodePtr(const void *a, const void *b)
{
	const spgNodePtr *aa = (const spgNodePtr *) a;
	const spgNodePtr *bb = (const spgNodePtr *) b;

	return aa->c - bb->c;
}