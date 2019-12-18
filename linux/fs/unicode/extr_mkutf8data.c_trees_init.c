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
struct unicode_data {unsigned int correction; } ;
struct tree {int dummy; } ;
struct TYPE_3__ {unsigned int maxage; char* type; int /*<<< orphan*/  childnode; int /*<<< orphan*/  leaf_emit; int /*<<< orphan*/  leaf_index; int /*<<< orphan*/  leaf_size; int /*<<< orphan*/  leaf_print; int /*<<< orphan*/  leaf_equal; void* leaf_mark; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE ; 
 unsigned int* ages ; 
 TYPE_1__* calloc (int,int) ; 
 void* correction_mark ; 
 struct unicode_data* corrections ; 
 int corrections_count ; 
 int /*<<< orphan*/  nfdi_emit ; 
 int /*<<< orphan*/  nfdi_equal ; 
 int /*<<< orphan*/  nfdi_index ; 
 void* nfdi_mark ; 
 int /*<<< orphan*/  nfdi_print ; 
 int /*<<< orphan*/  nfdi_size ; 
 int /*<<< orphan*/  nfdicf_emit ; 
 int /*<<< orphan*/  nfdicf_equal ; 
 int /*<<< orphan*/  nfdicf_index ; 
 void* nfdicf_mark ; 
 int /*<<< orphan*/  nfdicf_print ; 
 int /*<<< orphan*/  nfdicf_size ; 
 TYPE_1__* trees ; 
 int trees_count ; 

__attribute__((used)) static void trees_init(void)
{
	struct unicode_data *data;
	unsigned int maxage;
	unsigned int nextage;
	int count;
	int i;
	int j;

	/* Count the number of different ages. */
	count = 0;
	nextage = (unsigned int)-1;
	do {
		maxage = nextage;
		nextage = 0;
		for (i = 0; i <= corrections_count; i++) {
			data = &corrections[i];
			if (nextage < data->correction &&
			    data->correction < maxage)
				nextage = data->correction;
		}
		count++;
	} while (nextage);

	/* Two trees per age: nfdi and nfdicf */
	trees_count = count * 2;
	trees = calloc(trees_count, sizeof(struct tree));

	/* Assign ages to the trees. */
	count = trees_count;
	nextage = (unsigned int)-1;
	do {
		maxage = nextage;
		trees[--count].maxage = maxage;
		trees[--count].maxage = maxage;
		nextage = 0;
		for (i = 0; i <= corrections_count; i++) {
			data = &corrections[i];
			if (nextage < data->correction &&
			    data->correction < maxage)
				nextage = data->correction;
		}
	} while (nextage);

	/* The ages assigned above are off by one. */
	for (i = 0; i != trees_count; i++) {
		j = 0;
		while (ages[j] < trees[i].maxage)
			j++;
		trees[i].maxage = ages[j-1];
	}

	/* Set up the forwarding between trees. */
	trees[trees_count-2].next = &trees[trees_count-1];
	trees[trees_count-1].leaf_mark = nfdi_mark;
	trees[trees_count-2].leaf_mark = nfdicf_mark;
	for (i = 0; i != trees_count-2; i += 2) {
		trees[i].next = &trees[trees_count-2];
		trees[i].leaf_mark = correction_mark;
		trees[i+1].next = &trees[trees_count-1];
		trees[i+1].leaf_mark = correction_mark;
	}

	/* Assign the callouts. */
	for (i = 0; i != trees_count; i += 2) {
		trees[i].type = "nfdicf";
		trees[i].leaf_equal = nfdicf_equal;
		trees[i].leaf_print = nfdicf_print;
		trees[i].leaf_size = nfdicf_size;
		trees[i].leaf_index = nfdicf_index;
		trees[i].leaf_emit = nfdicf_emit;

		trees[i+1].type = "nfdi";
		trees[i+1].leaf_equal = nfdi_equal;
		trees[i+1].leaf_print = nfdi_print;
		trees[i+1].leaf_size = nfdi_size;
		trees[i+1].leaf_index = nfdi_index;
		trees[i+1].leaf_emit = nfdi_emit;
	}

	/* Finish init. */
	for (i = 0; i != trees_count; i++)
		trees[i].childnode = NODE;
}