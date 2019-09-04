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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int id; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* soc_ids ; 
 unsigned int socinfo_to_major (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *socinfo_to_soc_id(u32 socinfo)
{
	unsigned int id = socinfo_to_major(socinfo);
	int i;

	for (i = 0 ; i < ARRAY_SIZE(soc_ids) ; ++i) {
		if (soc_ids[i].id == id)
			return soc_ids[i].name;
	}

	return "Unknown";
}