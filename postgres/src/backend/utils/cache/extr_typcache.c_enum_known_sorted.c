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
struct TYPE_3__ {scalar_t__ bitmap_base; int /*<<< orphan*/  sorted_values; } ;
typedef  TYPE_1__ TypeCacheEnumData ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int bms_is_member (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
enum_known_sorted(TypeCacheEnumData *enumdata, Oid arg)
{
	Oid			offset;

	if (arg < enumdata->bitmap_base)
		return false;
	offset = arg - enumdata->bitmap_base;
	if (offset > (Oid) INT_MAX)
		return false;
	return bms_is_member((int) offset, enumdata->sorted_values);
}