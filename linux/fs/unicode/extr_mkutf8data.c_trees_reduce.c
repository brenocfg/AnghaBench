#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* type; int maxage; int index; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  emit (TYPE_1__*,void*) ; 
 int index_nodes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mark_nodes (TYPE_1__*) ; 
 void* nfdi ; 
 TYPE_1__* nfdi_tree ; 
 void* nfdicf ; 
 TYPE_1__* nfdicf_tree ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  prune (TYPE_1__*) ; 
 scalar_t__ size_nodes (TYPE_1__*) ; 
 TYPE_1__* trees ; 
 int trees_count ; 
 void* utf8data ; 
 int utf8data_size ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void trees_reduce(void)
{
	int i;
	int size;
	int changed;

	for (i = 0; i != trees_count; i++)
		prune(&trees[i]);
	for (i = 0; i != trees_count; i++)
		mark_nodes(&trees[i]);
	do {
		size = 0;
		for (i = 0; i != trees_count; i++)
			size = index_nodes(&trees[i], size);
		changed = 0;
		for (i = 0; i != trees_count; i++)
			changed += size_nodes(&trees[i]);
	} while (changed);

	utf8data = calloc(size, 1);
	utf8data_size = size;
	for (i = 0; i != trees_count; i++)
		emit(&trees[i], utf8data);

	if (verbose > 0) {
		for (i = 0; i != trees_count; i++) {
			printf("%s_%x idx %d\n",
				trees[i].type, trees[i].maxage, trees[i].index);
		}
	}

	nfdi = utf8data + trees[trees_count-1].index;
	nfdicf = utf8data + trees[trees_count-2].index;

	nfdi_tree = &trees[trees_count-1];
	nfdicf_tree = &trees[trees_count-2];
}