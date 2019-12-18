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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct stat {size_t st_size; } ;

/* Variables and functions */
 size_t DHP_HEADER_SIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int buffalo_crc (int*,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int fstat (int,struct stat*) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int open (char*,int,...) ; 
 char* progname ; 
 int /*<<< orphan*/  read (int,int*,size_t) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write (int,int*,size_t) ; 

int
main(int argc, char *argv[])
{
	struct stat in_st;
	size_t size;
	uint32_t crc;
	int in, out;
	uint8_t *buf;

	progname = argv[0];

	if (argc != 3)
		usage();

	if ((in = open(argv[1], O_RDONLY)) == -1)
		err(EXIT_FAILURE, "%s", argv[1]);

	if (fstat(in, &in_st) == -1)
		err(EXIT_FAILURE, "%s", argv[1]);

	size = DHP_HEADER_SIZE + in_st.st_size;

	if ((buf = malloc(size)) == NULL)
		err(EXIT_FAILURE, "malloc");

	memset(buf, 0, DHP_HEADER_SIZE);
	buf[0x0] = 0x62;
	buf[0x1] = 0x67;
	buf[0x2] = 0x6e;
	buf[0xb] = 0xb1;
	buf[0xc] = (size >> 24) & 0xff;
	buf[0xd] = (size >> 16) & 0xff;
	buf[0xe] = (size >> 8) & 0xff;
	buf[0xf] = size & 0xff;

	read(in, &buf[DHP_HEADER_SIZE], in_st.st_size);
	close(in);

	crc = buffalo_crc(buf, size);
	buf[0x10] = (crc >> 24) & 0xff;
	buf[0x11] = (crc >> 16) & 0xff;
	buf[0x12] = (crc >> 8) & 0xff;
	buf[0x13] = crc & 0xff;

	if ((out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		err(EXIT_FAILURE, "%s", argv[2]);
	write(out, buf, size);
	close(out);

	free(buf);

	return EXIT_SUCCESS;
}