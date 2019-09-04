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
struct device_node {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_SVR ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static unsigned int soc_info(unsigned int *rev_h, unsigned int *rev_l)
{
	struct device_node *np;
	const char *soc_string;
	unsigned int svr;
	unsigned int soc;

	/* Find the CPU node */
	np = of_find_node_by_type(NULL, "cpu");
	if (!np)
		return 0;
	/* Find the compatible property */
	soc_string = of_get_property(np, "compatible", NULL);
	if (!soc_string)
		/* No compatible property, so try the name. */
		soc_string = np->name;

	/* Extract the SOC number from the "PowerPC," string */
	if ((sscanf(soc_string, "PowerPC,%u", &soc) != 1) || !soc)
		return 0;

	/* Get the revision from the SVR */
	svr = mfspr(SPRN_SVR);
	*rev_h = (svr >> 4) & 0xf;
	*rev_l = svr & 0xf;

	return soc;
}