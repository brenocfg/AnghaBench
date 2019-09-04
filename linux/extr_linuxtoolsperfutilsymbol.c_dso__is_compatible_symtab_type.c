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
struct dso {int symtab_type; int /*<<< orphan*/  kernel; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;

/* Variables and functions */
#define  DSO_BINARY_TYPE__BUILDID_DEBUGINFO 147 
#define  DSO_BINARY_TYPE__BUILD_ID_CACHE 146 
#define  DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO 145 
#define  DSO_BINARY_TYPE__DEBUGLINK 144 
#define  DSO_BINARY_TYPE__FEDORA_DEBUGINFO 143 
#define  DSO_BINARY_TYPE__GUEST_KALLSYMS 142 
#define  DSO_BINARY_TYPE__GUEST_KCORE 141 
#define  DSO_BINARY_TYPE__GUEST_KMODULE 140 
#define  DSO_BINARY_TYPE__GUEST_KMODULE_COMP 139 
#define  DSO_BINARY_TYPE__GUEST_VMLINUX 138 
#define  DSO_BINARY_TYPE__JAVA_JIT 137 
#define  DSO_BINARY_TYPE__KALLSYMS 136 
#define  DSO_BINARY_TYPE__KCORE 135 
#define  DSO_BINARY_TYPE__NOT_FOUND 134 
#define  DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO 133 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_DSO 132 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE 131 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP 130 
#define  DSO_BINARY_TYPE__UBUNTU_DEBUGINFO 129 
#define  DSO_BINARY_TYPE__VMLINUX 128 
 int /*<<< orphan*/  DSO_TYPE_GUEST_KERNEL ; 
 int /*<<< orphan*/  DSO_TYPE_KERNEL ; 
 int /*<<< orphan*/  DSO_TYPE_USER ; 

__attribute__((used)) static bool dso__is_compatible_symtab_type(struct dso *dso, bool kmod,
					   enum dso_binary_type type)
{
	switch (type) {
	case DSO_BINARY_TYPE__JAVA_JIT:
	case DSO_BINARY_TYPE__DEBUGLINK:
	case DSO_BINARY_TYPE__SYSTEM_PATH_DSO:
	case DSO_BINARY_TYPE__FEDORA_DEBUGINFO:
	case DSO_BINARY_TYPE__UBUNTU_DEBUGINFO:
	case DSO_BINARY_TYPE__BUILDID_DEBUGINFO:
	case DSO_BINARY_TYPE__OPENEMBEDDED_DEBUGINFO:
		return !kmod && dso->kernel == DSO_TYPE_USER;

	case DSO_BINARY_TYPE__KALLSYMS:
	case DSO_BINARY_TYPE__VMLINUX:
	case DSO_BINARY_TYPE__KCORE:
		return dso->kernel == DSO_TYPE_KERNEL;

	case DSO_BINARY_TYPE__GUEST_KALLSYMS:
	case DSO_BINARY_TYPE__GUEST_VMLINUX:
	case DSO_BINARY_TYPE__GUEST_KCORE:
		return dso->kernel == DSO_TYPE_GUEST_KERNEL;

	case DSO_BINARY_TYPE__GUEST_KMODULE:
	case DSO_BINARY_TYPE__GUEST_KMODULE_COMP:
	case DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE:
	case DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP:
		/*
		 * kernel modules know their symtab type - it's set when
		 * creating a module dso in machine__findnew_module_map().
		 */
		return kmod && dso->symtab_type == type;

	case DSO_BINARY_TYPE__BUILD_ID_CACHE:
	case DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO:
		return true;

	case DSO_BINARY_TYPE__NOT_FOUND:
	default:
		return false;
	}
}