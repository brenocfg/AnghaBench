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
struct printf_spec {int field_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_WIDTH_MAX ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 int clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_field_width(struct printf_spec *spec, int width)
{
	spec->field_width = width;
	if (WARN_ONCE(spec->field_width != width, "field width %d too large", width)) {
		spec->field_width = clamp(width, -FIELD_WIDTH_MAX, FIELD_WIDTH_MAX);
	}
}