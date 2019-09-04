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
struct version_info {int version; int /*<<< orphan*/  hdr_size; } ;
struct fdt_reserve_entry {int dummy; } ;
struct fdt_header {int /*<<< orphan*/  totalsize; } ;
struct dt_info {int /*<<< orphan*/  boot_cpuid_phys; int /*<<< orphan*/  reservelist; int /*<<< orphan*/  dt; } ;
struct data {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ALIGN (int,scalar_t__) ; 
 int ARRAY_SIZE (struct version_info*) ; 
 int /*<<< orphan*/  FDT_END ; 
 scalar_t__ alignsize ; 
 int /*<<< orphan*/  bin_emit_cell (struct data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin_emitter ; 
 int /*<<< orphan*/  cpu_to_fdt32 (int) ; 
 struct data data_append_align (struct data,int) ; 
 struct data data_append_data (struct data,struct fdt_header*,int /*<<< orphan*/ ) ; 
 struct data data_append_zeroes (struct data,int) ; 
 int /*<<< orphan*/  data_free (struct data) ; 
 struct data data_merge (struct data,struct data) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct data empty_data ; 
 int /*<<< orphan*/  errno ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 struct data flatten_reserve_list (int /*<<< orphan*/ ,struct version_info*) ; 
 int /*<<< orphan*/  flatten_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct data*,struct data*,struct version_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_fdt_header (struct fdt_header*,struct version_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ minsize ; 
 int padsize ; 
 int quiet ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct version_info* version_table ; 

void dt_to_blob(FILE *f, struct dt_info *dti, int version)
{
	struct version_info *vi = NULL;
	int i;
	struct data blob       = empty_data;
	struct data reservebuf = empty_data;
	struct data dtbuf      = empty_data;
	struct data strbuf     = empty_data;
	struct fdt_header fdt;
	int padlen = 0;

	for (i = 0; i < ARRAY_SIZE(version_table); i++) {
		if (version_table[i].version == version)
			vi = &version_table[i];
	}
	if (!vi)
		die("Unknown device tree blob version %d\n", version);

	flatten_tree(dti->dt, &bin_emitter, &dtbuf, &strbuf, vi);
	bin_emit_cell(&dtbuf, FDT_END);

	reservebuf = flatten_reserve_list(dti->reservelist, vi);

	/* Make header */
	make_fdt_header(&fdt, vi, reservebuf.len, dtbuf.len, strbuf.len,
			dti->boot_cpuid_phys);

	/*
	 * If the user asked for more space than is used, adjust the totalsize.
	 */
	if (minsize > 0) {
		padlen = minsize - fdt32_to_cpu(fdt.totalsize);
		if (padlen < 0) {
			padlen = 0;
			if (quiet < 1)
				fprintf(stderr,
					"Warning: blob size %d >= minimum size %d\n",
					fdt32_to_cpu(fdt.totalsize), minsize);
		}
	}

	if (padsize > 0)
		padlen = padsize;

	if (alignsize > 0)
		padlen = ALIGN(fdt32_to_cpu(fdt.totalsize) + padlen, alignsize)
			- fdt32_to_cpu(fdt.totalsize);

	if (padlen > 0) {
		int tsize = fdt32_to_cpu(fdt.totalsize);
		tsize += padlen;
		fdt.totalsize = cpu_to_fdt32(tsize);
	}

	/*
	 * Assemble the blob: start with the header, add with alignment
	 * the reserve buffer, add the reserve map terminating zeroes,
	 * the device tree itself, and finally the strings.
	 */
	blob = data_append_data(blob, &fdt, vi->hdr_size);
	blob = data_append_align(blob, 8);
	blob = data_merge(blob, reservebuf);
	blob = data_append_zeroes(blob, sizeof(struct fdt_reserve_entry));
	blob = data_merge(blob, dtbuf);
	blob = data_merge(blob, strbuf);

	/*
	 * If the user asked for more space than is used, pad out the blob.
	 */
	if (padlen > 0)
		blob = data_append_zeroes(blob, padlen);

	if (fwrite(blob.val, blob.len, 1, f) != 1) {
		if (ferror(f))
			die("Error writing device tree blob: %s\n",
			    strerror(errno));
		else
			die("Short write on device tree blob\n");
	}

	/*
	 * data_merge() frees the right-hand element so only the blob
	 * remains to be freed.
	 */
	data_free(blob);
}