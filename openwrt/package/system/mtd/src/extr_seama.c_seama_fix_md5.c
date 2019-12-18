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
struct seama_entity_header {int /*<<< orphan*/  md5; int /*<<< orphan*/  size; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  htonl (size_t) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 size_t pread (int,char*,size_t,size_t) ; 
 int quiet ; 
 int /*<<< orphan*/  stderr ; 

int
seama_fix_md5(struct seama_entity_header *shdr, int fd, size_t data_offset, size_t data_size)
{
	char *buf;
	ssize_t res;
	MD5_CTX ctx;
	unsigned char digest[16];
	int i;
	int err = 0;

	buf = malloc(data_size);
	if (!buf) {
		err = -ENOMEM;
		goto err_out;
	}

	res = pread(fd, buf, data_size, data_offset);
	if (res != data_size) {
		perror("pread");
		err = -EIO;
		goto err_free;
	}

	MD5_Init(&ctx);
	MD5_Update(&ctx, buf, data_size);
	MD5_Final(digest, &ctx);

	if (!memcmp(digest, shdr->md5, sizeof(digest))) {
		if (quiet < 2)
			fprintf(stderr, "the header is fixed already\n");
		return -1;
	}

	if (quiet < 2) {
		fprintf(stderr, "new size:%u, new MD5: ", data_size);
		for (i = 0; i < sizeof(digest); i++)
			fprintf(stderr, "%02x", digest[i]);

		fprintf(stderr, "\n");
	}

	/* update the size in the image */
	shdr->size = htonl(data_size);

	/* update the checksum in the image */
	memcpy(shdr->md5, digest, sizeof(digest));

err_free:
	free(buf);
err_out:
	return err;
}