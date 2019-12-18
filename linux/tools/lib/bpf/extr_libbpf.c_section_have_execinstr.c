#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  elf; } ;
struct bpf_object {TYPE_1__ efile; } ;
struct TYPE_6__ {int sh_flags; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int SHF_EXECINSTR ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static bool section_have_execinstr(struct bpf_object *obj, int idx)
{
	Elf_Scn *scn;
	GElf_Shdr sh;

	scn = elf_getscn(obj->efile.elf, idx);
	if (!scn)
		return false;

	if (gelf_getshdr(scn, &sh) != &sh)
		return false;

	if (sh.sh_flags & SHF_EXECINSTR)
		return true;

	return false;
}