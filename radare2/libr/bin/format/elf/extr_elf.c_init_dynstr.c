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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int e_shnum; } ;
struct TYPE_7__ {char* shstrtab; size_t shstrtab_size; char* dynstr; scalar_t__ size; scalar_t__ dynstr_size; TYPE_2__* shdr; int /*<<< orphan*/  b; TYPE_1__ ehdr; } ;
struct TYPE_6__ {size_t sh_name; scalar_t__ sh_type; scalar_t__ sh_size; scalar_t__ sh_offset; } ;
typedef  TYPE_3__ ELFOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ SHT_STRTAB ; 
 int /*<<< orphan*/  bprintf (char*) ; 
 scalar_t__ calloc (scalar_t__,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static bool init_dynstr(ELFOBJ *bin) {
	int i, r;
	const char *section_name = NULL;
	if (!bin || !bin->shdr) {
		return false;
	}
	if (!bin->shstrtab) {
		return false;
	}
	for (i = 0; i < bin->ehdr.e_shnum; ++i) {
		if (bin->shdr[i].sh_name > bin->shstrtab_size) {
			return false;
		}
		section_name = &bin->shstrtab[bin->shdr[i].sh_name];
		if (bin->shdr[i].sh_type == SHT_STRTAB && !strcmp (section_name, ".dynstr")) {
			if (!(bin->dynstr = (char*) calloc (bin->shdr[i].sh_size + 1, sizeof (char)))) {
				bprintf("Cannot allocate memory for dynamic strings\n");
				return false;
			}
			if (bin->shdr[i].sh_offset > bin->size) {
				return false;
			}
			if (bin->shdr[i].sh_offset + bin->shdr[i].sh_size > bin->size) {
				return false;
			}
			if (bin->shdr[i].sh_offset + bin->shdr[i].sh_size < bin->shdr[i].sh_size) {
				return false;
			}
			r = r_buf_read_at (bin->b, bin->shdr[i].sh_offset, (ut8*)bin->dynstr, bin->shdr[i].sh_size);
			if (r < 1) {
				R_FREE (bin->dynstr);
				bin->dynstr_size = 0;
				return false;
			}
			bin->dynstr_size = bin->shdr[i].sh_size;
			return true;
		}
	}
	return false;
}