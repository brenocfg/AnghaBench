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
struct params {int serialize_startup; int data_reads; int data_writes; int data_backwards; int data_rand_walk; int nr_loops; int init_random; char* mb_global_str; int nr_proc; int nr_threads; int nr_secs; int run_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void init_params(struct params *p, const char *name, int argc, const char **argv)
{
	int i;

	printf("\n # Running %s \"perf bench numa", name);

	for (i = 0; i < argc; i++)
		printf(" %s", argv[i]);

	printf("\"\n");

	memset(p, 0, sizeof(*p));

	/* Initialize nonzero defaults: */

	p->serialize_startup		= 1;
	p->data_reads			= true;
	p->data_writes			= true;
	p->data_backwards		= true;
	p->data_rand_walk		= true;
	p->nr_loops			= -1;
	p->init_random			= true;
	p->mb_global_str		= "1";
	p->nr_proc			= 1;
	p->nr_threads			= 1;
	p->nr_secs			= 5;
	p->run_all			= argc == 1;
}