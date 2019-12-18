#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sym {int size; int address; scalar_t__ content; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {scalar_t__* e_ident; int e_shoff; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_SYM ; 
 scalar_t__ CURRENT_ELFCLASS ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LSIZE_SYM ; 
 int /*<<< orphan*/  USED_SYM ; 
 scalar_t__ endianness () ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  get_symbol_from_map (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sym*) ; 
 int /*<<< orphan*/  get_symbol_from_table (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sym*) ; 
 int /*<<< orphan*/ * get_symbol_table (TYPE_1__*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 TYPE_1__* map_file (char*,int*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_sym (TYPE_1__*,struct sym*) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 char* read_file (char*,int*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int main(int argc, char **argv)
{
	char *system_map_file = NULL;
	char *vmlinux_file = NULL;
	char *cert_file = NULL;
	int vmlinux_size;
	int cert_size;
	Elf_Ehdr *hdr;
	char *cert;
	FILE *system_map;
	unsigned long *lsize;
	int *used;
	int opt;
	Elf_Shdr *symtab = NULL;
	struct sym cert_sym, lsize_sym, used_sym;

	while ((opt = getopt(argc, argv, "b:c:s:")) != -1) {
		switch (opt) {
		case 's':
			system_map_file = optarg;
			break;
		case 'b':
			vmlinux_file = optarg;
			break;
		case 'c':
			cert_file = optarg;
			break;
		default:
			break;
		}
	}

	if (!vmlinux_file || !cert_file) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	cert = read_file(cert_file, &cert_size);
	if (!cert)
		exit(EXIT_FAILURE);

	hdr = map_file(vmlinux_file, &vmlinux_size);
	if (!hdr)
		exit(EXIT_FAILURE);

	if (vmlinux_size < sizeof(*hdr)) {
		err("Invalid ELF file.\n");
		exit(EXIT_FAILURE);
	}

	if ((hdr->e_ident[EI_MAG0] != ELFMAG0) ||
	    (hdr->e_ident[EI_MAG1] != ELFMAG1) ||
	    (hdr->e_ident[EI_MAG2] != ELFMAG2) ||
	    (hdr->e_ident[EI_MAG3] != ELFMAG3)) {
		err("Invalid ELF magic.\n");
		exit(EXIT_FAILURE);
	}

	if (hdr->e_ident[EI_CLASS] != CURRENT_ELFCLASS) {
		err("ELF class mismatch.\n");
		exit(EXIT_FAILURE);
	}

	if (hdr->e_ident[EI_DATA] != endianness()) {
		err("ELF endian mismatch.\n");
		exit(EXIT_FAILURE);
	}

	if (hdr->e_shoff > vmlinux_size) {
		err("Could not find section header.\n");
		exit(EXIT_FAILURE);
	}

	symtab = get_symbol_table(hdr);
	if (!symtab) {
		warn("Could not find the symbol table.\n");
		if (!system_map_file) {
			err("Please provide a System.map file.\n");
			print_usage(argv[0]);
			exit(EXIT_FAILURE);
		}

		system_map = fopen(system_map_file, "r");
		if (!system_map) {
			perror(system_map_file);
			exit(EXIT_FAILURE);
		}
		get_symbol_from_map(hdr, system_map, CERT_SYM, &cert_sym);
		get_symbol_from_map(hdr, system_map, USED_SYM, &used_sym);
		get_symbol_from_map(hdr, system_map, LSIZE_SYM, &lsize_sym);
		cert_sym.size = used_sym.address - cert_sym.address;
	} else {
		info("Symbol table found.\n");
		if (system_map_file)
			warn("System.map is ignored.\n");
		get_symbol_from_table(hdr, symtab, CERT_SYM, &cert_sym);
		get_symbol_from_table(hdr, symtab, USED_SYM, &used_sym);
		get_symbol_from_table(hdr, symtab, LSIZE_SYM, &lsize_sym);
	}

	if (!cert_sym.offset || !lsize_sym.offset || !used_sym.offset)
		exit(EXIT_FAILURE);

	print_sym(hdr, &cert_sym);
	print_sym(hdr, &used_sym);
	print_sym(hdr, &lsize_sym);

	lsize = (unsigned long *)lsize_sym.content;
	used = (int *)used_sym.content;

	if (cert_sym.size < cert_size) {
		err("Certificate is larger than the reserved area!\n");
		exit(EXIT_FAILURE);
	}

	/* If the existing cert is the same, don't overwrite */
	if (cert_size == *used &&
	    strncmp(cert_sym.content, cert, cert_size) == 0) {
		warn("Certificate was already inserted.\n");
		exit(EXIT_SUCCESS);
	}

	if (*used > 0)
		warn("Replacing previously inserted certificate.\n");

	memcpy(cert_sym.content, cert, cert_size);
	if (cert_size < cert_sym.size)
		memset(cert_sym.content + cert_size,
			0, cert_sym.size - cert_size);

	*lsize = *lsize + cert_size - *used;
	*used = cert_size;
	info("Inserted the contents of %s into %lx.\n", cert_file,
						cert_sym.address);
	info("Used %d bytes out of %d bytes reserved.\n", *used,
						 cert_sym.size);
	exit(EXIT_SUCCESS);
}