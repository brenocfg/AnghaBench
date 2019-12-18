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
struct TYPE_4__ {scalar_t__ name; scalar_t__ group; } ;
typedef  TYPE_1__ key_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int inifile_key_cmp(const key_type *k1, const key_type *k2)
{
	assert(k1->group && k1->name && k2->group && k2->name);

	if (!strcasecmp(k1->group, k2->group)) {
		if (!strcasecmp(k1->name, k2->name)) {
			return 0;
		} else {
			return 1;
		}
	} else {
		return 2;
	}
}