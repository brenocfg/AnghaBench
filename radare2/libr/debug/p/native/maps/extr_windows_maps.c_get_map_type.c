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
struct TYPE_3__ {int Type; } ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;

/* Variables and functions */
#define  MEM_IMAGE 130 
#define  MEM_MAPPED 129 
#define  MEM_PRIVATE 128 

__attribute__((used)) static char *get_map_type(MEMORY_BASIC_INFORMATION *mbi) {
	char *type;
	switch (mbi->Type) {
	case MEM_IMAGE:
		type = "IMAGE";
		break;
	case MEM_MAPPED:
		type = "MAPPED";
		break;
	case MEM_PRIVATE:
		type = "PRIVATE";
		break;
	default:
		type = "UNKNOWN";
	}
	return type;
}