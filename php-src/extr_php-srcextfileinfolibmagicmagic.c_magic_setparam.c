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
typedef  void* uint16_t ;
struct magic_set {size_t bytes_max; void* elf_notes_max; void* elf_shnum_max; void* elf_phnum_max; void* name_max; void* indir_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  MAGIC_PARAM_BYTES_MAX 134 
#define  MAGIC_PARAM_ELF_NOTES_MAX 133 
#define  MAGIC_PARAM_ELF_PHNUM_MAX 132 
#define  MAGIC_PARAM_ELF_SHNUM_MAX 131 
#define  MAGIC_PARAM_INDIR_MAX 130 
#define  MAGIC_PARAM_NAME_MAX 129 
#define  MAGIC_PARAM_REGEX_MAX 128 
 int /*<<< orphan*/  errno ; 

int
magic_setparam(struct magic_set *ms, int param, const void *val)
{
	switch (param) {
	case MAGIC_PARAM_INDIR_MAX:
		ms->indir_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_NAME_MAX:
		ms->name_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_ELF_PHNUM_MAX:
		ms->elf_phnum_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_ELF_SHNUM_MAX:
		ms->elf_shnum_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_ELF_NOTES_MAX:
		ms->elf_notes_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_REGEX_MAX:
		ms->elf_notes_max = (uint16_t)*(const size_t *)val;
		return 0;
	case MAGIC_PARAM_BYTES_MAX:
		ms->bytes_max = *(const size_t *)val;
		return 0;
	default:
		errno = EINVAL;
		return -1;
	}
}