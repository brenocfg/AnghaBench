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
struct TYPE_2__ {scalar_t__ field_type; int /*<<< orphan*/  field_name; } ;
typedef  TYPE_1__ TIFFField ;

/* Variables and functions */
 scalar_t__ TIFF_ANY ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tagNameCompare(const void* a, const void* b)
{
	const TIFFField* ta = *(const TIFFField**) a;
	const TIFFField* tb = *(const TIFFField**) b;
	int ret = strcmp(ta->field_name, tb->field_name);

	if (ret)
		return ret;
	else
		return (ta->field_type == TIFF_ANY) ?
			0 : ((int)tb->field_type - (int)ta->field_type);
}