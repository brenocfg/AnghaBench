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
struct buffalo_tag3 {int dummy; } ;
struct buffalo_tag2 {int dummy; } ;
struct buffalo_tag {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ dhp ; 
 int /*<<< orphan*/  fixup_tag (unsigned char*,int) ; 
 int /*<<< orphan*/  fixup_tag2 (unsigned char*,int) ; 
 int /*<<< orphan*/  fixup_tag3 (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__* fsize ; 
 scalar_t__ get_file_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ifname ; 
 unsigned char* malloc (int) ; 
 int num_files ; 
 int /*<<< orphan*/  ofname ; 
 int read_file_to_buf (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int write_buf_to_file (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int tag_file(void)
{
	unsigned char *buf;
	ssize_t offset;
	ssize_t hdrlen;
	ssize_t buflen;
	int err;
	int ret = -1;
	int i;

	if (dhp)
		hdrlen = sizeof(struct buffalo_tag3);
	else if (num_files == 1)
		hdrlen = sizeof(struct buffalo_tag);
	else
		hdrlen = sizeof(struct buffalo_tag2);

	buflen = hdrlen;

	for (i = 0; i < num_files; i++) {
		fsize[i] = get_file_size(ifname[i]);
		if (fsize[i] < 0) {
			ERR("unable to get size of '%s'", ifname[i]);
			goto out;
		}
		buflen += fsize[i];
	}

	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto out;
	}

	offset = hdrlen;
	for (i = 0; i < num_files; i++) {
		err = read_file_to_buf(ifname[i], buf + offset, fsize[i]);
		if (err) {
			ERR("unable to read from file '%s'", ifname[i]);
			goto free_buf;
		}

		offset += fsize[i];
	}

	if (dhp)
		fixup_tag3(buf, fsize[0] + 200);
	else if (num_files == 1)
		fixup_tag(buf, buflen);
	else
		fixup_tag2(buf, buflen);

	err = write_buf_to_file(ofname, buf, buflen);
	if (err) {
		ERR("unable to write to file '%s'", ofname);
		goto free_buf;
	}

	ret = 0;

free_buf:
	free(buf);
out:
	return ret;
}