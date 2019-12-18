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
typedef  int u_int16_t ;
struct product {int vendorid; int productid; char const* name; struct product* next; } ;

/* Variables and functions */
 size_t hashnum (int) ; 
 struct product** products ; 

const char *names_product(u_int16_t vendorid, u_int16_t productid)
{
	struct product *p;

	p = products[hashnum((vendorid << 16) | productid)];
	for (; p; p = p->next)
		if (p->vendorid == vendorid && p->productid == productid)
			return p->name;
	return NULL;
}