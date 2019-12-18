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
typedef  int ssize_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BUF_SIZE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERRS (char*,char*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,float,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* pad ; 
 int pad_len ; 
 int /*<<< orphan*/  pad_to_stdout ; 
 int /*<<< orphan*/  stderr ; 
 int write (int,char*,int) ; 
 int xtra_offset ; 

__attribute__((used)) static int pad_image(char *name, uint32_t pad_mask)
{
	char *buf;
	int fd;
	int outfd;
	ssize_t in_len;
	ssize_t out_len;
	int ret = -1;

	buf = malloc(BUF_SIZE);
	if (!buf) {
		ERR("No memory for buffer");
		goto out;
	}

	fd = open(name, O_RDWR);
	if (fd < 0) {
		ERRS("Unable to open %s", name);
		goto free_buf;
	}

	in_len = lseek(fd, 0, SEEK_END);
	if (in_len < 0)
		goto close;

	if (!pad_to_stdout)
		outfd = fd;
	else
		outfd = STDOUT_FILENO;

	memset(buf, '\xff', BUF_SIZE);

	in_len += xtra_offset;

	out_len = in_len;
	while (pad_mask) {
		uint32_t mask;
		ssize_t t;
		int i;

		for (i = 10; i < 32; i++) {
			mask = 1UL << i;
			if (pad_mask & mask)
				break;
		}

		in_len = ALIGN(in_len, mask);

		for (i = 10; i < 32; i++) {
			mask = 1UL << i;
			if ((in_len & (mask - 1)) == 0)
				pad_mask &= ~mask;
		}

		fprintf(stderr, "padding image to %08x\n", (unsigned int) in_len - xtra_offset);

		while (out_len < in_len) {
			ssize_t len;

			len = in_len - out_len;
			if (len > BUF_SIZE)
				len = BUF_SIZE;

			t = write(outfd, buf, len);
			if (t != len) {
				ERRS("Unable to write to %s", name);
				goto close;
			}

			out_len += len;
		}

		/* write out the JFFS end-of-filesystem marker */
		t = write(outfd, pad, pad_len);
		if (t != pad_len) {
			ERRS("Unable to write to %s", name);
			goto close;
		}
		out_len += pad_len;
	}

	ret = 0;

close:
	close(fd);
free_buf:
	free(buf);
out:
	return ret;
}