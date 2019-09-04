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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_asm_insns (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * get_last_jit_image (char*,unsigned int,unsigned int*) ; 
 char* get_log_buff (char*,unsigned int*) ; 
 unsigned int getopt (int,char**,char*) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_log_buff (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ write (int,int /*<<< orphan*/ *,unsigned int) ; 

int main(int argc, char **argv)
{
	unsigned int len, klen, opt, opcodes = 0;
	char *kbuff, *file = NULL;
	char *ofile = NULL;
	int ofd;
	ssize_t nr;
	uint8_t *pos;
	uint8_t *image = NULL;

	while ((opt = getopt(argc, argv, "of:O:")) != -1) {
		switch (opt) {
		case 'o':
			opcodes = 1;
			break;
		case 'O':
			ofile = optarg;
			break;
		case 'f':
			file = optarg;
			break;
		default:
			usage();
			return -1;
		}
	}

	bfd_init();

	kbuff = get_log_buff(file, &klen);
	if (!kbuff) {
		fprintf(stderr, "Could not retrieve log buffer!\n");
		return -1;
	}

	image = get_last_jit_image(kbuff, klen, &len);
	if (!image) {
		fprintf(stderr, "No JIT image found!\n");
		goto done;
	}
	if (!ofile) {
		get_asm_insns(image, len, opcodes);
		goto done;
	}

	ofd = open(ofile, O_WRONLY | O_CREAT | O_TRUNC, DEFFILEMODE);
	if (ofd < 0) {
		fprintf(stderr, "Could not open file %s for writing: ", ofile);
		perror(NULL);
		goto done;
	}
	pos = image;
	do {
		nr = write(ofd, pos, len);
		if (nr < 0) {
			fprintf(stderr, "Could not write data to %s: ", ofile);
			perror(NULL);
			goto done;
		}
		len -= nr;
		pos += nr;
	} while (len);
	close(ofd);

done:
	put_log_buff(kbuff);
	free(image);
	return 0;
}