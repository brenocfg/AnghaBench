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
struct seama_entity_header {scalar_t__ magic; int /*<<< orphan*/  size; int /*<<< orphan*/  metasize; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEAMA_MAGIC ; 
 int /*<<< orphan*/  close (int) ; 
 int erasesize ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int mtd_check_open (char const*) ; 
 scalar_t__ mtd_erase_block (int,size_t) ; 
 size_t mtdsize ; 
 size_t ntohl (int /*<<< orphan*/ ) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pread (int,char*,int,size_t) ; 
 int pwrite (int,char*,int,size_t) ; 
 int quiet ; 
 scalar_t__ seama_fix_md5 (struct seama_entity_header*,int,size_t,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 

int
mtd_fixseama(const char *mtd, size_t offset, size_t data_size)
{
	int fd;
	char *first_block;
	ssize_t res;
	size_t block_offset;
	size_t data_offset;
	struct seama_entity_header *shdr;

	if (quiet < 2)
		fprintf(stderr, "Trying to fix SEAMA header in %s at 0x%x...\n",
			mtd, offset);

	block_offset = offset & ~(erasesize - 1);
	offset -= block_offset;

	fd = mtd_check_open(mtd);
	if(fd < 0) {
		fprintf(stderr, "Could not open mtd device: %s\n", mtd);
		exit(1);
	}

	if (block_offset + erasesize > mtdsize) {
		fprintf(stderr, "Offset too large, device size 0x%x\n",
			mtdsize);
		exit(1);
	}

	first_block = malloc(erasesize);
	if (!first_block) {
		perror("malloc");
		exit(1);
	}

	res = pread(fd, first_block, erasesize, block_offset);
	if (res != erasesize) {
		perror("pread");
		exit(1);
	}

	shdr = (struct seama_entity_header *)(first_block + offset);
	if (shdr->magic != htonl(SEAMA_MAGIC)) {
		fprintf(stderr, "No SEAMA header found\n");
		exit(1);
	} else if (!ntohl(shdr->size)) {
		fprintf(stderr, "Seama entity with empty image\n");
		exit(1);
	}

	data_offset = offset + sizeof(struct seama_entity_header) + ntohs(shdr->metasize);
	if (!data_size)
		data_size = mtdsize - data_offset;
	if (data_size > ntohl(shdr->size))
		data_size = ntohl(shdr->size);
	if (seama_fix_md5(shdr, fd, data_offset, data_size))
		goto out;

	if (mtd_erase_block(fd, block_offset)) {
		fprintf(stderr, "Can't erease block at 0x%x (%s)\n",
			block_offset, strerror(errno));
		exit(1);
	}

	if (quiet < 2)
		fprintf(stderr, "Rewriting block at 0x%x\n", block_offset);

	if (pwrite(fd, first_block, erasesize, block_offset) != erasesize) {
		fprintf(stderr, "Error writing block (%s)\n", strerror(errno));
		exit(1);
	}

	if (quiet < 2)
		fprintf(stderr, "Done.\n");

out:
	close (fd);
	sync();

	return 0;
}