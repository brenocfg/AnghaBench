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
struct seama_entity_header {int /*<<< orphan*/  imagesize; int /*<<< orphan*/  metasize; int /*<<< orphan*/  magic; } ;
typedef  struct seama_entity_header uint8_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int SEAMA_MAGIC ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int entity_idx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 size_t fread (struct seama_entity_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t fwrite (struct seama_entity_header*,int,size_t,int /*<<< orphan*/ *) ; 
 int oseama_min (int,size_t) ; 
 int /*<<< orphan*/  out_path ; 
 char* seama_path ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int oseama_extract_entity(FILE *seama, FILE *out) {
	struct seama_entity_header hdr;
	size_t bytes, metasize, imagesize, length;
	uint8_t buf[1024];
	int i = 0;
	int err = 0;

	while ((bytes = fread(&hdr, 1, sizeof(hdr), seama)) == sizeof(hdr)) {
		if (be32_to_cpu(hdr.magic) != SEAMA_MAGIC) {
			fprintf(stderr, "Invalid Seama magic: 0x%08x\n", be32_to_cpu(hdr.magic));
			err =  -EINVAL;
			break;
		}
		metasize = be16_to_cpu(hdr.metasize);
		imagesize = be32_to_cpu(hdr.imagesize);

		if (i != entity_idx) {
			fseek(seama, metasize + imagesize, SEEK_CUR);
			i++;
			continue;
		}

		fseek(seama, -sizeof(hdr), SEEK_CUR);

		length = sizeof(hdr) + metasize + imagesize;
		while ((bytes = fread(buf, 1, oseama_min(sizeof(buf), length), seama)) > 0) {
			if (fwrite(buf, 1, bytes, out) != bytes) {
				fprintf(stderr, "Couldn't write %zu B to %s\n", bytes, out_path);
				err = -EIO;
				break;
			}
			length -= bytes;
		}

		if (length) {
			fprintf(stderr, "Couldn't extract whole entity %d from %s (%zu B left)\n", entity_idx, seama_path, length);
			err = -EIO;
			break;
		}

		break;
	}

	return err;
}