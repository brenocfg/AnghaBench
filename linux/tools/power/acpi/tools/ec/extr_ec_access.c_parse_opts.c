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

/* Variables and functions */
 scalar_t__ EC_SPACE_SIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read_byte_offset ; 
 int read_mode ; 
 int /*<<< orphan*/  sleep_time ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_byte_offset ; 
 int write_value ; 

void parse_opts(int argc, char *argv[])
{
	int c;

	while ((c = getopt(argc, argv, "rs:b:w:v:h")) != -1) {

		switch (c) {
		case 'r':
			if (read_mode != -1)
				usage(argv[0], EXIT_FAILURE);
			read_mode = 1;
			break;
		case 's':
			if (read_mode != -1 && read_mode != 1)
				usage(argv[0], EXIT_FAILURE);

			sleep_time = atoi(optarg);
			if (sleep_time <= 0) {
				sleep_time = 0;
				usage(argv[0], EXIT_FAILURE);
				printf("Bad sleep time: %s\n", optarg);
			}
			break;
		case 'b':
			if (read_mode != -1)
				usage(argv[0], EXIT_FAILURE);
			read_mode = 1;
			read_byte_offset = strtoul(optarg, NULL, 16);
			break;
		case 'w':
			if (read_mode != -1)
				usage(argv[0], EXIT_FAILURE);
			read_mode = 0;
			write_byte_offset = strtoul(optarg, NULL, 16);
			break;
		case 'v':
			write_value = strtoul(optarg, NULL, 16);
			break;
		case 'h':
			usage(argv[0], EXIT_SUCCESS);
		default:
			fprintf(stderr, "Unknown option!\n");
			usage(argv[0], EXIT_FAILURE);
		}
	}
	if (read_mode == 0) {
		if (write_byte_offset < 0 ||
		    write_byte_offset >= EC_SPACE_SIZE) {
			fprintf(stderr, "Wrong byte offset 0x%.2x, valid: "
				"[0-0x%.2x]\n",
				write_byte_offset, EC_SPACE_SIZE - 1);
			usage(argv[0], EXIT_FAILURE);
		}
		if (write_value < 0 ||
		    write_value >= 255) {
			fprintf(stderr, "Wrong byte offset 0x%.2x, valid:"
				"[0-0xff]\n", write_byte_offset);
			usage(argv[0], EXIT_FAILURE);
		}
	}
	if (read_mode == 1 && read_byte_offset != -1) {
		if (read_byte_offset < -1 ||
		    read_byte_offset >= EC_SPACE_SIZE) {
			fprintf(stderr, "Wrong byte offset 0x%.2x, valid: "
				"[0-0x%.2x]\n",
				read_byte_offset, EC_SPACE_SIZE - 1);
			usage(argv[0], EXIT_FAILURE);
		}
	}
	/* Add additional parameter checks here */
}