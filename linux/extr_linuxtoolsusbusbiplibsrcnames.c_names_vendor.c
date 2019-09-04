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
typedef  scalar_t__ u_int16_t ;
struct vendor {scalar_t__ vendorid; char const* name; struct vendor* next; } ;

/* Variables and functions */
 size_t hashnum (scalar_t__) ; 
 struct vendor** vendors ; 

const char *names_vendor(u_int16_t vendorid)
{
	struct vendor *v;

	v = vendors[hashnum(vendorid)];
	for (; v; v = v->next)
		if (v->vendorid == vendorid)
			return v->name;
	return NULL;
}