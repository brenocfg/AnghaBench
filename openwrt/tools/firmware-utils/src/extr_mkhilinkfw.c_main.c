#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct option {char* member_0; char member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int off_t ;
struct TYPE_2__ {int /*<<< orphan*/  ih_magic; int /*<<< orphan*/  ih_size; } ;
typedef  TYPE_1__ image_header_t ;
typedef  int /*<<< orphan*/  const_DES_cblock ;

/* Variables and functions */
 scalar_t__ DES_KEY ; 
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int IH_MAGIC ; 
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  copy_file (scalar_t__,int) ; 
 int creat (char*,int) ; 
 int /*<<< orphan*/  do_decrypt (char*,int) ; 
 int /*<<< orphan*/  do_encrypt (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_cleanup ; 
 scalar_t__ fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ftruncate (scalar_t__,int) ; 
 int getopt_long (int,char**,char*,struct option*,int*) ; 
 int lseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int min (int,int) ; 
 char* mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
#define  no_argument 129 
 int ntohl (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
#define  required_argument 128 
 int /*<<< orphan*/  schedule ; 
 int /*<<< orphan*/  show_usage (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ temp_fd ; 
 int /*<<< orphan*/  tmpfile () ; 

int main(int argc, char **argv)
{
	int encrypt_opt = 0;
	int decrypt_opt = 0;
	int input_opt = 0;
	int output_opt = 0;
	char *input_filename = NULL;
	char *output_filename = NULL;
 
	int input_fd;
	int output_fd;
	off_t file_len;
	char *p;
	char buf[sizeof(image_header_t) + 3];
	image_header_t *header;
 
	while (1) {
		static struct option long_options[] = {
			{"encrypt", no_argument,       0, 'e'},
			{"decrypt", no_argument,       0, 'd'},
			{"input",   required_argument, 0, 'i'},
			{"output",  required_argument, 0, 'o'},
			{0,         0,                 0, 0  }
		};
		int option_index = 0;
		int c = getopt_long(argc, argv, "dei:o:",
		                long_options, &option_index);
		if (c == -1)
			break;
 
		switch (c) {
		case 'd':
			decrypt_opt++;
			if (decrypt_opt > 1) {
				fprintf(stderr, "%s: decrypt may only be specified once\n",
				        argv[0]);
				show_usage(argv[0]);
			}
			break;
 
		case 'e':
			encrypt_opt++;
			if (encrypt_opt > 1) {
				fprintf(stderr, "%s: encrypt may only be specified once\n",
				        argv[0]);
				show_usage(argv[0]);
			}
			break;
 
		case 'i':
			input_opt++;
			if (input_opt > 1) {
				fprintf(stderr, "%s: only one input file may be specified\n",
				        argv[0]);
				show_usage(argv[0]);
			}
			if (strcmp("-", optarg) != 0) {
				input_filename = optarg;
			}
			break;
 
		case 'o':
			output_opt++;
			if (output_opt > 1) {
				fprintf(stderr, "%s: only one output file may be specified\n",
				        argv[0]);
				show_usage(argv[0]);
			}
			if (strcmp("-", optarg) != 0) {
				output_filename = optarg;
			}
			break;
 
		case '?':
			exit(-1);
 
		default:
			abort();
		}
	}
 
	if (decrypt_opt && encrypt_opt) {
		fprintf(stderr, "%s: decrypt and encrypt may not be used together\n",
		        argv[0]);
		show_usage(argv[0]);
	}
 
	if (!decrypt_opt && !encrypt_opt) {
		fprintf(stderr, "%s: neither decrypt or encrypt were specified\n",
		        argv[0]);
		show_usage(argv[0]);
	}
 
	temp_fd = fileno(tmpfile());
	if (temp_fd < 0) {
		fprintf(stderr, "Can't create temporary file\n");
		exit(EXIT_FAILURE);
	}
 
	atexit(exit_cleanup);
	DES_set_key_unchecked((const_DES_cblock *)DES_KEY, &schedule);
 
	if (input_filename) {
		input_fd = open(input_filename, O_RDONLY);
		if (input_fd < 0) {
			fprintf(stderr, "Can't open %s for reading: %s\n", input_filename,
			        strerror(errno));
			exit(EXIT_FAILURE);
		}
		copy_file(input_fd, temp_fd);
		close(input_fd);
	}
	else {
		copy_file(STDIN_FILENO, temp_fd);
	}
 
	file_len = lseek(temp_fd, 0, SEEK_CUR);
	if (file_len < 64) {
		fprintf(stderr, "Not enough data\n");
		exit(EXIT_FAILURE);
	}
 
	p = mmap(0, file_len, PROT_READ|PROT_WRITE, MAP_SHARED, temp_fd, 0);
	if (p == MAP_FAILED) {
		fprintf(stderr, "mmap failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}	
 
	if (encrypt_opt) {
		header = (image_header_t *)p;
		off_t len = min(file_len,
		                ntohl(header->ih_size) + sizeof(image_header_t));
		if (ntohl(header->ih_magic) != IH_MAGIC) {
			fprintf(stderr, "Header magic incorrect: "
			        "expected 0x%08X, got 0x%08X\n",
			        IH_MAGIC, ntohl(header->ih_magic));
			munmap(p, file_len);
			exit(EXIT_FAILURE);
		}
		do_encrypt(p, len);
		munmap(p, file_len);
		if (len != file_len) {
			if (ftruncate(temp_fd, len) < 0) {
				fprintf(stderr, "ftruncate failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}		
	}
 
	if (decrypt_opt) {
		off_t header_len = min(file_len, sizeof(image_header_t) + 3);
		memcpy(buf, p, header_len);
		do_decrypt(buf, header_len);
		header = (image_header_t *)buf;
		if (ntohl(header->ih_magic) != IH_MAGIC) {
			fprintf(stderr, "Header magic incorrect: "
			        "expected 0x%08X, got 0x%08X\n",
			        IH_MAGIC, ntohl(header->ih_magic));
			exit(EXIT_FAILURE);
		}
		do_decrypt(p, file_len);
		munmap(p, file_len);
	}
 
	lseek(temp_fd, 0, SEEK_SET);
	if (output_filename) {
		output_fd = creat(output_filename, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if (output_fd < 0) {
			fprintf(stderr, "Can't open %s for writing: %s\n",
			        output_filename, strerror(errno));
			exit(EXIT_FAILURE);
		}
		copy_file(temp_fd, output_fd);
		close(output_fd);
	}
	else {
		copy_file(temp_fd, STDOUT_FILENO);
	}
 
	exit(EXIT_SUCCESS);
	return 0;
}