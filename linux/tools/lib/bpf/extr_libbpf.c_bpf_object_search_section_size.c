#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_8__ {int /*<<< orphan*/ * elf; TYPE_3__ ehdr; } ;
struct bpf_object {int /*<<< orphan*/  path; TYPE_1__ efile; } ;
struct TYPE_11__ {size_t d_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  TYPE_3__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_4__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 TYPE_4__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warning (char*,int,char const*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int bpf_object_search_section_size(const struct bpf_object *obj,
					  const char *name, size_t *d_size)
{
	const GElf_Ehdr *ep = &obj->efile.ehdr;
	Elf *elf = obj->efile.elf;
	Elf_Scn *scn = NULL;
	int idx = 0;

	while ((scn = elf_nextscn(elf, scn)) != NULL) {
		const char *sec_name;
		Elf_Data *data;
		GElf_Shdr sh;

		idx++;
		if (gelf_getshdr(scn, &sh) != &sh) {
			pr_warning("failed to get section(%d) header from %s\n",
				   idx, obj->path);
			return -EIO;
		}

		sec_name = elf_strptr(elf, ep->e_shstrndx, sh.sh_name);
		if (!sec_name) {
			pr_warning("failed to get section(%d) name from %s\n",
				   idx, obj->path);
			return -EIO;
		}

		if (strcmp(name, sec_name))
			continue;

		data = elf_getdata(scn, 0);
		if (!data) {
			pr_warning("failed to get section(%d) data from %s(%s)\n",
				   idx, name, obj->path);
			return -EIO;
		}

		*d_size = data->d_size;
		return 0;
	}

	return -ENOENT;
}