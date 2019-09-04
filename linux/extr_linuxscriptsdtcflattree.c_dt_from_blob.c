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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  totalsize_buf ;
typedef  int /*<<< orphan*/  totalsize ;
struct reserve_info {int dummy; } ;
struct node {int dummy; } ;
struct inbuf {int dummy; } ;
struct fdt_header {char off_dt_struct; char off_dt_strings; char off_mem_rsvmap; char version; char boot_cpuid_phys; char size_dt_strings; char size_dt_struct; void* totalsize; void* magic; } ;
struct dt_info {int dummy; } ;
typedef  int /*<<< orphan*/  magic_buf ;
typedef  int /*<<< orphan*/  magic ;
typedef  char fdt32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DTSF_V1 ; 
 scalar_t__ FDT_BEGIN_NODE ; 
 scalar_t__ FDT_END ; 
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ FDT_V1_SIZE ; 
 int FTF_FULLPATH ; 
 int FTF_NAMEPROPS ; 
 int FTF_NOPS ; 
 int FTF_VARALIGN ; 
 struct dt_info* build_dt_info (int /*<<< orphan*/ ,struct reserve_info*,struct node*,scalar_t__) ; 
 void* cpu_to_fdt32 (scalar_t__) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fdt32_to_cpu (char) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 struct reserve_info* flat_read_mem_reserve (struct inbuf*) ; 
 scalar_t__ flat_read_word (struct inbuf*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inbuf_init (struct inbuf*,char*,char*) ; 
 int /*<<< orphan*/ * srcfile_relative_open (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct node* unflatten_tree (struct inbuf*,struct inbuf*,char*,int) ; 
 char* xmalloc (scalar_t__) ; 

struct dt_info *dt_from_blob(const char *fname)
{
	FILE *f;
	fdt32_t magic_buf, totalsize_buf;
	uint32_t magic, totalsize, version, size_dt, boot_cpuid_phys;
	uint32_t off_dt, off_str, off_mem_rsvmap;
	int rc;
	char *blob;
	struct fdt_header *fdt;
	char *p;
	struct inbuf dtbuf, strbuf;
	struct inbuf memresvbuf;
	int sizeleft;
	struct reserve_info *reservelist;
	struct node *tree;
	uint32_t val;
	int flags = 0;

	f = srcfile_relative_open(fname, NULL);

	rc = fread(&magic_buf, sizeof(magic_buf), 1, f);
	if (ferror(f))
		die("Error reading DT blob magic number: %s\n",
		    strerror(errno));
	if (rc < 1) {
		if (feof(f))
			die("EOF reading DT blob magic number\n");
		else
			die("Mysterious short read reading magic number\n");
	}

	magic = fdt32_to_cpu(magic_buf);
	if (magic != FDT_MAGIC)
		die("Blob has incorrect magic number\n");

	rc = fread(&totalsize_buf, sizeof(totalsize_buf), 1, f);
	if (ferror(f))
		die("Error reading DT blob size: %s\n", strerror(errno));
	if (rc < 1) {
		if (feof(f))
			die("EOF reading DT blob size\n");
		else
			die("Mysterious short read reading blob size\n");
	}

	totalsize = fdt32_to_cpu(totalsize_buf);
	if (totalsize < FDT_V1_SIZE)
		die("DT blob size (%d) is too small\n", totalsize);

	blob = xmalloc(totalsize);

	fdt = (struct fdt_header *)blob;
	fdt->magic = cpu_to_fdt32(magic);
	fdt->totalsize = cpu_to_fdt32(totalsize);

	sizeleft = totalsize - sizeof(magic) - sizeof(totalsize);
	p = blob + sizeof(magic)  + sizeof(totalsize);

	while (sizeleft) {
		if (feof(f))
			die("EOF before reading %d bytes of DT blob\n",
			    totalsize);

		rc = fread(p, 1, sizeleft, f);
		if (ferror(f))
			die("Error reading DT blob: %s\n",
			    strerror(errno));

		sizeleft -= rc;
		p += rc;
	}

	off_dt = fdt32_to_cpu(fdt->off_dt_struct);
	off_str = fdt32_to_cpu(fdt->off_dt_strings);
	off_mem_rsvmap = fdt32_to_cpu(fdt->off_mem_rsvmap);
	version = fdt32_to_cpu(fdt->version);
	boot_cpuid_phys = fdt32_to_cpu(fdt->boot_cpuid_phys);

	if (off_mem_rsvmap >= totalsize)
		die("Mem Reserve structure offset exceeds total size\n");

	if (off_dt >= totalsize)
		die("DT structure offset exceeds total size\n");

	if (off_str > totalsize)
		die("String table offset exceeds total size\n");

	if (version >= 3) {
		uint32_t size_str = fdt32_to_cpu(fdt->size_dt_strings);
		if ((off_str+size_str < off_str) || (off_str+size_str > totalsize))
			die("String table extends past total size\n");
		inbuf_init(&strbuf, blob + off_str, blob + off_str + size_str);
	} else {
		inbuf_init(&strbuf, blob + off_str, blob + totalsize);
	}

	if (version >= 17) {
		size_dt = fdt32_to_cpu(fdt->size_dt_struct);
		if ((off_dt+size_dt < off_dt) || (off_dt+size_dt > totalsize))
			die("Structure block extends past total size\n");
	}

	if (version < 16) {
		flags |= FTF_FULLPATH | FTF_NAMEPROPS | FTF_VARALIGN;
	} else {
		flags |= FTF_NOPS;
	}

	inbuf_init(&memresvbuf,
		   blob + off_mem_rsvmap, blob + totalsize);
	inbuf_init(&dtbuf, blob + off_dt, blob + totalsize);

	reservelist = flat_read_mem_reserve(&memresvbuf);

	val = flat_read_word(&dtbuf);

	if (val != FDT_BEGIN_NODE)
		die("Device tree blob doesn't begin with FDT_BEGIN_NODE (begins with 0x%08x)\n", val);

	tree = unflatten_tree(&dtbuf, &strbuf, "", flags);

	val = flat_read_word(&dtbuf);
	if (val != FDT_END)
		die("Device tree blob doesn't end with FDT_END\n");

	free(blob);

	fclose(f);

	return build_dt_info(DTSF_V1, reservelist, tree, boot_cpuid_phys);
}