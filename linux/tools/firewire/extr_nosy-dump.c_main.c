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
typedef  int uint32_t ;
struct pollfd {int fd; scalar_t__ revents; void* events; } ;
typedef  int /*<<< orphan*/  poptContext ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  NOSY_IOC_FILTER ; 
 int /*<<< orphan*/  NOSY_IOC_START ; 
 int /*<<< orphan*/  O_RDWR ; 
 void* POLLIN ; 
 int /*<<< orphan*/  SIGINT ; 
 int STDIN_FILENO ; 
 int TCODE_CYCLE_START ; 
 int TCODE_STREAM_DATA ; 
 char* VERSION ; 
#define  VIEW_PACKET 130 
#define  VIEW_STATS 129 
#define  VIEW_TRANSACTION 128 
 int /*<<< orphan*/  _IOLBF ; 
 scalar_t__ __BYTE_ORDER ; 
 scalar_t__ __LITTLE_ENDIAN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_packet (int*,int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,...) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_cycle_start ; 
 char* option_input ; 
 int /*<<< orphan*/  option_iso ; 
 char* option_nosy_device ; 
 char* option_output ; 
 scalar_t__ option_version ; 
 int /*<<< orphan*/  option_view ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  poptFreeContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poptGetContext (int /*<<< orphan*/ *,int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int poptGetNextOpt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poptPrintUsage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_packet (int*,int) ; 
 int /*<<< orphan*/  print_stats (int*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int,...) ; 
 scalar_t__ run ; 
 int /*<<< orphan*/  set_input_mode () ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sys_sigint_handler ; 

int main(int argc, const char *argv[])
{
	uint32_t buf[128 * 1024];
	uint32_t filter;
	int length, retval, view;
	int fd = -1;
	FILE *output = NULL, *input = NULL;
	poptContext con;
	char c;
	struct pollfd pollfds[2];

	sys_sigint_handler = signal(SIGINT, sigint_handler);

	con = poptGetContext(NULL, argc, argv, options, 0);
	retval = poptGetNextOpt(con);
	if (retval < -1) {
		poptPrintUsage(con, stdout, 0);
		return -1;
	}

	if (option_version) {
		printf("dump tool for nosy sniffer, version %s\n", VERSION);
		return 0;
	}

	if (__BYTE_ORDER != __LITTLE_ENDIAN)
		fprintf(stderr, "warning: nosy has only been tested on little "
			"endian machines\n");

	if (option_input != NULL) {
		input = fopen(option_input, "r");
		if (input == NULL) {
			fprintf(stderr, "Could not open %s, %m\n", option_input);
			return -1;
		}
	} else {
		fd = open(option_nosy_device, O_RDWR);
		if (fd < 0) {
			fprintf(stderr, "Could not open %s, %m\n", option_nosy_device);
			return -1;
		}
		set_input_mode();
	}

	if (strcmp(option_view, "transaction") == 0)
		view = VIEW_TRANSACTION;
	else if (strcmp(option_view, "stats") == 0)
		view = VIEW_STATS;
	else
		view = VIEW_PACKET;

	if (option_output) {
		output = fopen(option_output, "w");
		if (output == NULL) {
			fprintf(stderr, "Could not open %s, %m\n", option_output);
			return -1;
		}
	}

	setvbuf(stdout, NULL, _IOLBF, BUFSIZ);

	filter = ~0;
	if (!option_iso)
		filter &= ~(1 << TCODE_STREAM_DATA);
	if (!option_cycle_start)
		filter &= ~(1 << TCODE_CYCLE_START);
	if (view == VIEW_STATS)
		filter = ~(1 << TCODE_CYCLE_START);

	ioctl(fd, NOSY_IOC_FILTER, filter);

	ioctl(fd, NOSY_IOC_START);

	pollfds[0].fd = fd;
	pollfds[0].events = POLLIN;
	pollfds[1].fd = STDIN_FILENO;
	pollfds[1].events = POLLIN;

	while (run) {
		if (input != NULL) {
			if (fread(&length, sizeof length, 1, input) != 1)
				return 0;
			fread(buf, 1, length, input);
		} else {
			poll(pollfds, 2, -1);
			if (pollfds[1].revents) {
				read(STDIN_FILENO, &c, sizeof c);
				switch (c) {
				case 'q':
					if (output != NULL)
						fclose(output);
					return 0;
				}
			}

			if (pollfds[0].revents)
				length = read(fd, buf, sizeof buf);
			else
				continue;
		}

		if (output != NULL) {
			fwrite(&length, sizeof length, 1, output);
			fwrite(buf, 1, length, output);
		}

		switch (view) {
		case VIEW_TRANSACTION:
			handle_packet(buf, length);
			break;
		case VIEW_PACKET:
			print_packet(buf, length);
			break;
		case VIEW_STATS:
			print_stats(buf, length);
			break;
		}
	}

	if (output != NULL)
		fclose(output);

	close(fd);

	poptFreeContext(con);

	return 0;
}