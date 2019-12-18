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
typedef  int /*<<< orphan*/  value ;
struct isst_clos_config {int epp; int clos_prop_prio; int clos_min; int clos_max; int clos_desired; } ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  format_and_print (int /*<<< orphan*/ *,int,char*,char*) ; 
 int get_physical_die_id (int) ; 
 int get_physical_package_id (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void isst_clos_display_information(int cpu, FILE *outf, int clos,
				   struct isst_clos_config *clos_config)
{
	char header[256];
	char value[256];

	snprintf(header, sizeof(header), "package-%d",
		 get_physical_package_id(cpu));
	format_and_print(outf, 1, header, NULL);
	snprintf(header, sizeof(header), "die-%d", get_physical_die_id(cpu));
	format_and_print(outf, 2, header, NULL);
	snprintf(header, sizeof(header), "cpu-%d", cpu);
	format_and_print(outf, 3, header, NULL);

	snprintf(header, sizeof(header), "core-power");
	format_and_print(outf, 4, header, NULL);

	snprintf(header, sizeof(header), "clos");
	snprintf(value, sizeof(value), "%d", clos);
	format_and_print(outf, 5, header, value);

	snprintf(header, sizeof(header), "epp");
	snprintf(value, sizeof(value), "%d", clos_config->epp);
	format_and_print(outf, 5, header, value);

	snprintf(header, sizeof(header), "clos-proportional-priority");
	snprintf(value, sizeof(value), "%d", clos_config->clos_prop_prio);
	format_and_print(outf, 5, header, value);

	snprintf(header, sizeof(header), "clos-min");
	snprintf(value, sizeof(value), "%d", clos_config->clos_min);
	format_and_print(outf, 5, header, value);

	snprintf(header, sizeof(header), "clos-max");
	snprintf(value, sizeof(value), "%d", clos_config->clos_max);
	format_and_print(outf, 5, header, value);

	snprintf(header, sizeof(header), "clos-desired");
	snprintf(value, sizeof(value), "%d", clos_config->clos_desired);
	format_and_print(outf, 5, header, value);

	format_and_print(outf, 1, NULL, NULL);
}