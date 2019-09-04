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
struct product {int vendorid; int productid; struct product* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int hashnum (int) ; 
 struct product* my_malloc (scalar_t__) ; 
 struct product** products ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int new_product(const char *name, u_int16_t vendorid,
		       u_int16_t productid)
{
	struct product *p;
	unsigned int h = hashnum((vendorid << 16) | productid);

	p = products[h];
	for (; p; p = p->next)
		if (p->vendorid == vendorid && p->productid == productid)
			return -1;
	p = my_malloc(sizeof(struct product) + strlen(name));
	if (!p)
		return -1;
	strcpy(p->name, name);
	p->vendorid = vendorid;
	p->productid = productid;
	p->next = products[h];
	products[h] = p;
	return 0;
}