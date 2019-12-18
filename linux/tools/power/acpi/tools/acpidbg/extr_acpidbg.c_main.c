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
 scalar_t__ ACPI_AML_BATCH ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 char* acpi_aml_batch_cmd ; 
 int /*<<< orphan*/  acpi_aml_file_path ; 
 int /*<<< orphan*/  acpi_aml_flush (int) ; 
 int /*<<< orphan*/  acpi_aml_loop (int) ; 
 scalar_t__ acpi_aml_mode ; 
 int /*<<< orphan*/  acpi_aml_set_fl (int /*<<< orphan*/ ,int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char **argv)
{
	int fd = -1;
	int ch;
	int len;
	int ret = EXIT_SUCCESS;

	while ((ch = getopt(argc, argv, "b:f:h")) != -1) {
		switch (ch) {
		case 'b':
			if (acpi_aml_batch_cmd) {
				fprintf(stderr, "Already specify %s\n",
					acpi_aml_batch_cmd);
				ret = EXIT_FAILURE;
				goto exit;
			}
			len = strlen(optarg);
			acpi_aml_batch_cmd = calloc(len + 2, 1);
			if (!acpi_aml_batch_cmd) {
				perror("calloc");
				ret = EXIT_FAILURE;
				goto exit;
			}
			memcpy(acpi_aml_batch_cmd, optarg, len);
			acpi_aml_batch_cmd[len] = '\n';
			acpi_aml_mode = ACPI_AML_BATCH;
			break;
		case 'f':
			acpi_aml_file_path = optarg;
			break;
		case 'h':
			usage(stdout, argv[0]);
			goto exit;
			break;
		case '?':
		default:
			usage(stderr, argv[0]);
			ret = EXIT_FAILURE;
			goto exit;
			break;
		}
	}

	fd = open(acpi_aml_file_path, O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		perror("open");
		ret = EXIT_FAILURE;
		goto exit;
	}
	acpi_aml_set_fl(STDIN_FILENO, O_NONBLOCK);
	acpi_aml_set_fl(STDOUT_FILENO, O_NONBLOCK);

	if (acpi_aml_mode == ACPI_AML_BATCH)
		acpi_aml_flush(fd);
	acpi_aml_loop(fd);

exit:
	if (fd >= 0)
		close(fd);
	if (acpi_aml_batch_cmd)
		free(acpi_aml_batch_cmd);
	return ret;
}