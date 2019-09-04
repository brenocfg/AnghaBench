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
typedef  int /*<<< orphan*/  serr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int READ_SIZE ; 
 int STRERR_BUFSIZE ; 
 int WEXITSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char const*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
read_from_pipe(const char *cmd, void **p_buf, size_t *p_read_sz)
{
	int err = 0;
	void *buf = NULL;
	FILE *file = NULL;
	size_t read_sz = 0, buf_sz = 0;
	char serr[STRERR_BUFSIZE];

	file = popen(cmd, "r");
	if (!file) {
		pr_err("ERROR: unable to popen cmd: %s\n",
		       str_error_r(errno, serr, sizeof(serr)));
		return -EINVAL;
	}

	while (!feof(file) && !ferror(file)) {
		/*
		 * Make buf_sz always have obe byte extra space so we
		 * can put '\0' there.
		 */
		if (buf_sz - read_sz < READ_SIZE + 1) {
			void *new_buf;

			buf_sz = read_sz + READ_SIZE + 1;
			new_buf = realloc(buf, buf_sz);

			if (!new_buf) {
				pr_err("ERROR: failed to realloc memory\n");
				err = -ENOMEM;
				goto errout;
			}

			buf = new_buf;
		}
		read_sz += fread(buf + read_sz, 1, READ_SIZE, file);
	}

	if (buf_sz - read_sz < 1) {
		pr_err("ERROR: internal error\n");
		err = -EINVAL;
		goto errout;
	}

	if (ferror(file)) {
		pr_err("ERROR: error occurred when reading from pipe: %s\n",
		       str_error_r(errno, serr, sizeof(serr)));
		err = -EIO;
		goto errout;
	}

	err = WEXITSTATUS(pclose(file));
	file = NULL;
	if (err) {
		err = -EINVAL;
		goto errout;
	}

	/*
	 * If buf is string, give it terminal '\0' to make our life
	 * easier. If buf is not string, that '\0' is out of space
	 * indicated by read_sz so caller won't even notice it.
	 */
	((char *)buf)[read_sz] = '\0';

	if (!p_buf)
		free(buf);
	else
		*p_buf = buf;

	if (p_read_sz)
		*p_read_sz = read_sz;
	return 0;

errout:
	if (file)
		pclose(file);
	free(buf);
	if (p_buf)
		*p_buf = NULL;
	if (p_read_sz)
		*p_read_sz = 0;
	return err;
}