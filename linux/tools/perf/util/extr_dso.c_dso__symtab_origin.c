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
struct dso {size_t symtab_type; } ;

/* Variables and functions */
#define  DSO_BINARY_TYPE__BUILDID_DEBUGINFO 144 
#define  DSO_BINARY_TYPE__BUILD_ID_CACHE 143 
#define  DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO 142 
#define  DSO_BINARY_TYPE__DEBUGLINK 141 
#define  DSO_BINARY_TYPE__FEDORA_DEBUGINFO 140 
#define  DSO_BINARY_TYPE__GUEST_KALLSYMS 139 
#define  DSO_BINARY_TYPE__GUEST_KMODULE 138 
#define  DSO_BINARY_TYPE__GUEST_KMODULE_COMP 137 
#define  DSO_BINARY_TYPE__GUEST_VMLINUX 136 
#define  DSO_BINARY_TYPE__JAVA_JIT 135 
#define  DSO_BINARY_TYPE__KALLSYMS 134 
 size_t DSO_BINARY_TYPE__NOT_FOUND ; 
#define  DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO 133 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_DSO 132 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE 131 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP 130 
#define  DSO_BINARY_TYPE__UBUNTU_DEBUGINFO 129 
#define  DSO_BINARY_TYPE__VMLINUX 128 

char dso__symtab_origin(const struct dso *dso)
{
	static const char origin[] = {
		[DSO_BINARY_TYPE__KALLSYMS]			= 'k',
		[DSO_BINARY_TYPE__VMLINUX]			= 'v',
		[DSO_BINARY_TYPE__JAVA_JIT]			= 'j',
		[DSO_BINARY_TYPE__DEBUGLINK]			= 'l',
		[DSO_BINARY_TYPE__BUILD_ID_CACHE]		= 'B',
		[DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO]	= 'D',
		[DSO_BINARY_TYPE__FEDORA_DEBUGINFO]		= 'f',
		[DSO_BINARY_TYPE__UBUNTU_DEBUGINFO]		= 'u',
		[DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO]	= 'o',
		[DSO_BINARY_TYPE__BUILDID_DEBUGINFO]		= 'b',
		[DSO_BINARY_TYPE__SYSTEM_PATH_DSO]		= 'd',
		[DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE]		= 'K',
		[DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP]	= 'm',
		[DSO_BINARY_TYPE__GUEST_KALLSYMS]		= 'g',
		[DSO_BINARY_TYPE__GUEST_KMODULE]		= 'G',
		[DSO_BINARY_TYPE__GUEST_KMODULE_COMP]		= 'M',
		[DSO_BINARY_TYPE__GUEST_VMLINUX]		= 'V',
	};

	if (dso == NULL || dso->symtab_type == DSO_BINARY_TYPE__NOT_FOUND)
		return '!';
	return origin[dso->symtab_type];
}