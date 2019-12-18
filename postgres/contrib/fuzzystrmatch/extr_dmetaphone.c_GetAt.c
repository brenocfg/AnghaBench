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
struct TYPE_3__ {int length; scalar_t__* str; } ;
typedef  TYPE_1__ metastring ;

/* Variables and functions */

__attribute__((used)) static char
GetAt(metastring *s, int pos)
{
	if ((pos < 0) || (pos >= s->length))
		return '\0';

	return ((char) *(s->str + pos));
}