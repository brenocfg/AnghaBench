#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct elf_info {int size; scalar_t__ num_sections; scalar_t__ secindex_strings; scalar_t__ modinfo_len; unsigned int export_sec; unsigned int export_unused_sec; unsigned int export_gpl_sec; unsigned int export_unused_gpl_sec; unsigned int export_gpl_future_sec; scalar_t__* symtab_shndx_start; scalar_t__* symtab_shndx_stop; TYPE_1__* symtab_stop; TYPE_1__* symtab_start; void* strtab; void* ksymtab_strings; void* modinfo; TYPE_2__* sechdrs; TYPE_3__* hdr; } ;
struct TYPE_7__ {scalar_t__* e_ident; scalar_t__ e_type; scalar_t__ e_machine; scalar_t__ e_version; scalar_t__ e_entry; scalar_t__ e_phoff; scalar_t__ e_shoff; scalar_t__ e_flags; scalar_t__ e_ehsize; scalar_t__ e_phentsize; scalar_t__ e_phnum; scalar_t__ e_shentsize; scalar_t__ e_shnum; scalar_t__ e_shstrndx; } ;
struct TYPE_6__ {scalar_t__ sh_size; scalar_t__ sh_link; scalar_t__ sh_name; scalar_t__ sh_type; scalar_t__ sh_flags; scalar_t__ sh_addr; scalar_t__ sh_offset; scalar_t__ sh_info; scalar_t__ sh_addralign; scalar_t__ sh_entsize; } ;
struct TYPE_5__ {scalar_t__ st_shndx; scalar_t__ st_name; scalar_t__ st_value; scalar_t__ st_size; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf_Ehdr ;
typedef  scalar_t__ Elf32_Word ;

/* Variables and functions */
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ SHN_XINDEX ; 
 scalar_t__ SHT_NOBITS ; 
 scalar_t__ SHT_SYMTAB ; 
 scalar_t__ SHT_SYMTAB_SHNDX ; 
 void* TO_NATIVE (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 TYPE_3__* grab_file (char const*,int*) ; 
 scalar_t__ ignore_missing_files ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_elf(struct elf_info *info, const char *filename)
{
	unsigned int i;
	Elf_Ehdr *hdr;
	Elf_Shdr *sechdrs;
	Elf_Sym  *sym;
	const char *secstrings;
	unsigned int symtab_idx = ~0U, symtab_shndx_idx = ~0U;

	hdr = grab_file(filename, &info->size);
	if (!hdr) {
		if (ignore_missing_files) {
			fprintf(stderr, "%s: %s (ignored)\n", filename,
				strerror(errno));
			return 0;
		}
		perror(filename);
		exit(1);
	}
	info->hdr = hdr;
	if (info->size < sizeof(*hdr)) {
		/* file too small, assume this is an empty .o file */
		return 0;
	}
	/* Is this a valid ELF file? */
	if ((hdr->e_ident[EI_MAG0] != ELFMAG0) ||
	    (hdr->e_ident[EI_MAG1] != ELFMAG1) ||
	    (hdr->e_ident[EI_MAG2] != ELFMAG2) ||
	    (hdr->e_ident[EI_MAG3] != ELFMAG3)) {
		/* Not an ELF file - silently ignore it */
		return 0;
	}
	/* Fix endianness in ELF header */
	hdr->e_type      = TO_NATIVE(hdr->e_type);
	hdr->e_machine   = TO_NATIVE(hdr->e_machine);
	hdr->e_version   = TO_NATIVE(hdr->e_version);
	hdr->e_entry     = TO_NATIVE(hdr->e_entry);
	hdr->e_phoff     = TO_NATIVE(hdr->e_phoff);
	hdr->e_shoff     = TO_NATIVE(hdr->e_shoff);
	hdr->e_flags     = TO_NATIVE(hdr->e_flags);
	hdr->e_ehsize    = TO_NATIVE(hdr->e_ehsize);
	hdr->e_phentsize = TO_NATIVE(hdr->e_phentsize);
	hdr->e_phnum     = TO_NATIVE(hdr->e_phnum);
	hdr->e_shentsize = TO_NATIVE(hdr->e_shentsize);
	hdr->e_shnum     = TO_NATIVE(hdr->e_shnum);
	hdr->e_shstrndx  = TO_NATIVE(hdr->e_shstrndx);
	sechdrs = (void *)hdr + hdr->e_shoff;
	info->sechdrs = sechdrs;

	/* Check if file offset is correct */
	if (hdr->e_shoff > info->size) {
		fatal("section header offset=%lu in file '%s' is bigger than "
		      "filesize=%lu\n", (unsigned long)hdr->e_shoff,
		      filename, info->size);
		return 0;
	}

	if (hdr->e_shnum == SHN_UNDEF) {
		/*
		 * There are more than 64k sections,
		 * read count from .sh_size.
		 */
		info->num_sections = TO_NATIVE(sechdrs[0].sh_size);
	}
	else {
		info->num_sections = hdr->e_shnum;
	}
	if (hdr->e_shstrndx == SHN_XINDEX) {
		info->secindex_strings = TO_NATIVE(sechdrs[0].sh_link);
	}
	else {
		info->secindex_strings = hdr->e_shstrndx;
	}

	/* Fix endianness in section headers */
	for (i = 0; i < info->num_sections; i++) {
		sechdrs[i].sh_name      = TO_NATIVE(sechdrs[i].sh_name);
		sechdrs[i].sh_type      = TO_NATIVE(sechdrs[i].sh_type);
		sechdrs[i].sh_flags     = TO_NATIVE(sechdrs[i].sh_flags);
		sechdrs[i].sh_addr      = TO_NATIVE(sechdrs[i].sh_addr);
		sechdrs[i].sh_offset    = TO_NATIVE(sechdrs[i].sh_offset);
		sechdrs[i].sh_size      = TO_NATIVE(sechdrs[i].sh_size);
		sechdrs[i].sh_link      = TO_NATIVE(sechdrs[i].sh_link);
		sechdrs[i].sh_info      = TO_NATIVE(sechdrs[i].sh_info);
		sechdrs[i].sh_addralign = TO_NATIVE(sechdrs[i].sh_addralign);
		sechdrs[i].sh_entsize   = TO_NATIVE(sechdrs[i].sh_entsize);
	}
	/* Find symbol table. */
	secstrings = (void *)hdr + sechdrs[info->secindex_strings].sh_offset;
	for (i = 1; i < info->num_sections; i++) {
		const char *secname;
		int nobits = sechdrs[i].sh_type == SHT_NOBITS;

		if (!nobits && sechdrs[i].sh_offset > info->size) {
			fatal("%s is truncated. sechdrs[i].sh_offset=%lu > "
			      "sizeof(*hrd)=%zu\n", filename,
			      (unsigned long)sechdrs[i].sh_offset,
			      sizeof(*hdr));
			return 0;
		}
		secname = secstrings + sechdrs[i].sh_name;
		if (strcmp(secname, ".modinfo") == 0) {
			if (nobits)
				fatal("%s has NOBITS .modinfo\n", filename);
			info->modinfo = (void *)hdr + sechdrs[i].sh_offset;
			info->modinfo_len = sechdrs[i].sh_size;
		} else if (strcmp(secname, "__ksymtab") == 0)
			info->export_sec = i;
		else if (strcmp(secname, "__ksymtab_unused") == 0)
			info->export_unused_sec = i;
		else if (strcmp(secname, "__ksymtab_gpl") == 0)
			info->export_gpl_sec = i;
		else if (strcmp(secname, "__ksymtab_unused_gpl") == 0)
			info->export_unused_gpl_sec = i;
		else if (strcmp(secname, "__ksymtab_gpl_future") == 0)
			info->export_gpl_future_sec = i;
		else if (strcmp(secname, "__ksymtab_strings") == 0)
			info->ksymtab_strings = (void *)hdr +
						sechdrs[i].sh_offset -
						sechdrs[i].sh_addr;

		if (sechdrs[i].sh_type == SHT_SYMTAB) {
			unsigned int sh_link_idx;
			symtab_idx = i;
			info->symtab_start = (void *)hdr +
			    sechdrs[i].sh_offset;
			info->symtab_stop  = (void *)hdr +
			    sechdrs[i].sh_offset + sechdrs[i].sh_size;
			sh_link_idx = sechdrs[i].sh_link;
			info->strtab       = (void *)hdr +
			    sechdrs[sh_link_idx].sh_offset;
		}

		/* 32bit section no. table? ("more than 64k sections") */
		if (sechdrs[i].sh_type == SHT_SYMTAB_SHNDX) {
			symtab_shndx_idx = i;
			info->symtab_shndx_start = (void *)hdr +
			    sechdrs[i].sh_offset;
			info->symtab_shndx_stop  = (void *)hdr +
			    sechdrs[i].sh_offset + sechdrs[i].sh_size;
		}
	}
	if (!info->symtab_start)
		fatal("%s has no symtab?\n", filename);

	/* Fix endianness in symbols */
	for (sym = info->symtab_start; sym < info->symtab_stop; sym++) {
		sym->st_shndx = TO_NATIVE(sym->st_shndx);
		sym->st_name  = TO_NATIVE(sym->st_name);
		sym->st_value = TO_NATIVE(sym->st_value);
		sym->st_size  = TO_NATIVE(sym->st_size);
	}

	if (symtab_shndx_idx != ~0U) {
		Elf32_Word *p;
		if (symtab_idx != sechdrs[symtab_shndx_idx].sh_link)
			fatal("%s: SYMTAB_SHNDX has bad sh_link: %u!=%u\n",
			      filename, sechdrs[symtab_shndx_idx].sh_link,
			      symtab_idx);
		/* Fix endianness */
		for (p = info->symtab_shndx_start; p < info->symtab_shndx_stop;
		     p++)
			*p = TO_NATIVE(*p);
	}

	return 1;
}