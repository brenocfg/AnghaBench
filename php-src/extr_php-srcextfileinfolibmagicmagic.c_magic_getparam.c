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
struct magic_set {size_t indir_max; size_t name_max; size_t elf_phnum_max; size_t elf_shnum_max; size_t elf_notes_max; size_t regex_max; size_t bytes_max; } ;

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
magic_getparam(struct magic_set *ms, int param, void *val)
{
	switch (param) {
	case MAGIC_PARAM_INDIR_MAX:
		*(size_t *)val = ms->indir_max;
		return 0;
	case MAGIC_PARAM_NAME_MAX:
		*(size_t *)val = ms->name_max;
		return 0;
	case MAGIC_PARAM_ELF_PHNUM_MAX:
		*(size_t *)val = ms->elf_phnum_max;
		return 0;
	case MAGIC_PARAM_ELF_SHNUM_MAX:
		*(size_t *)val = ms->elf_shnum_max;
		return 0;
	case MAGIC_PARAM_ELF_NOTES_MAX:
		*(size_t *)val = ms->elf_notes_max;
		return 0;
	case MAGIC_PARAM_REGEX_MAX:
		*(size_t *)val = ms->regex_max;
		return 0;
	case MAGIC_PARAM_BYTES_MAX:
		*(size_t *)val = ms->bytes_max;
		return 0;
	default:
		errno = EINVAL;
		return -1;
	}
}