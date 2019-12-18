#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ip_type4 ;
struct TYPE_4__ {size_t counter; TYPE_1__** list; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFUNC () ; 
 size_t index_from_internal_ip (int /*<<< orphan*/ ) ; 
 TYPE_2__* internal_ips ; 

char *string_from_internal_ip(ip_type4 internalip) {
	PFUNC();
	char *res = NULL;
	uint32_t index = index_from_internal_ip(internalip);
	if(index < internal_ips->counter)
		res = internal_ips->list[index]->string;
	return res;
}