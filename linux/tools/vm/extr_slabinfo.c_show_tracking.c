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
struct slabinfo {char* name; } ;

/* Variables and functions */
 char* buffer ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_slab_obj (struct slabinfo*,char*) ; 

__attribute__((used)) static void show_tracking(struct slabinfo *s)
{
	printf("\n%s: Kernel object allocation\n", s->name);
	printf("-----------------------------------------------------------------------\n");
	if (read_slab_obj(s, "alloc_calls"))
		printf("%s", buffer);
	else
		printf("No Data\n");

	printf("\n%s: Kernel object freeing\n", s->name);
	printf("------------------------------------------------------------------------\n");
	if (read_slab_obj(s, "free_calls"))
		printf("%s", buffer);
	else
		printf("No Data\n");

}