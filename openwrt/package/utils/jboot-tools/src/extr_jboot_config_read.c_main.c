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
struct data_header {int dummy; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MAX_DATA_HEADER ; 
 int /*<<< orphan*/  VERBOSE (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/ * buffer ; 
 scalar_t__ config_size ; 
 int find_header (int /*<<< orphan*/ *,scalar_t__,struct data_header**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ifname ; 
 int mac_print ; 
 int /*<<< orphan*/ * ofname ; 
 void* optarg ; 
 int print_data ; 
 int /*<<< orphan*/  print_data_header (struct data_header*) ; 
 int /*<<< orphan*/  print_mac (struct data_header**,int) ; 
 int /*<<< orphan*/  progname ; 
 int read_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (void*,char*,scalar_t__*) ; 
 scalar_t__ start_offset ; 
 int /*<<< orphan*/  usage (int) ; 
 int verbose ; 
 int write_eeprom (struct data_header**,int) ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;
	int configs_counter = 0;
	struct data_header *configs_table[MAX_DATA_HEADER];
	buffer = NULL;
	config_size = 0;

	progname = basename(argv[0]);
	start_offset = 0;
	mac_print = 0;
	print_data = 0;
	verbose = 0;
	ofname = NULL;
	ifname = NULL;

	while (1) {
		int c;

		c = getopt(argc, argv, "de:hi:mo:pv");
		if (c == -1)
			break;

		switch (c) {
		case 'm':
			mac_print = 1;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'e':
			ofname = optarg;
			break;
		case 'o':
			sscanf(optarg, "0x%x", &start_offset);
			break;
		case 'p':
			print_data = 1;
			break;
		case 'v':
			verbose = 1;
			VERBOSE("Enable verbose!");
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (!ifname)
		usage(EXIT_FAILURE);

	ret = read_file(ifname);

	if (ret || config_size <= 0)
		goto out;

	configs_counter = find_header(buffer, config_size, configs_table);

	if (configs_counter <= 0)
		goto out_free_buf;

	if (print_data || verbose) {
		for (int i = 0; i < configs_counter; i++)
			print_data_header(configs_table[i]);
	}

	if (mac_print)
		print_mac(configs_table, configs_counter);

	ret = EXIT_SUCCESS;

	if (ofname)
		ret = write_eeprom(configs_table, configs_counter);

 out_free_buf:
	free(buffer);
 out:
	return ret;

}