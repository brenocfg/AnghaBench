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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ TypeCacheEntry ;

/* Variables and functions */
 int TCFLAGS_CHECKED_ELEM_PROPERTIES ; 
 int TCFLAGS_HAVE_ELEM_HASHING ; 
 int /*<<< orphan*/  cache_range_element_properties (TYPE_1__*) ; 

__attribute__((used)) static bool
range_element_has_hashing(TypeCacheEntry *typentry)
{
	if (!(typentry->flags & TCFLAGS_CHECKED_ELEM_PROPERTIES))
		cache_range_element_properties(typentry);
	return (typentry->flags & TCFLAGS_HAVE_ELEM_HASHING) != 0;
}