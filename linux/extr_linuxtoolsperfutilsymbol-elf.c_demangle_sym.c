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
struct dso {scalar_t__ kernel; } ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_NO_OPTS ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  JAVA_DEMANGLE_NORET ; 
 char* bfd_demangle (int /*<<< orphan*/ *,char const*,int) ; 
 char* java_demangle_sym (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rust_demangle_sym (char*) ; 
 scalar_t__ rust_is_mangled (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  want_demangle (int) ; 

__attribute__((used)) static char *demangle_sym(struct dso *dso, int kmodule, const char *elf_name)
{
	int demangle_flags = verbose > 0 ? (DMGL_PARAMS | DMGL_ANSI) : DMGL_NO_OPTS;
	char *demangled = NULL;

	/*
	 * We need to figure out if the object was created from C++ sources
	 * DWARF DW_compile_unit has this, but we don't always have access
	 * to it...
	 */
	if (!want_demangle(dso->kernel || kmodule))
	    return demangled;

	demangled = bfd_demangle(NULL, elf_name, demangle_flags);
	if (demangled == NULL)
		demangled = java_demangle_sym(elf_name, JAVA_DEMANGLE_NORET);
	else if (rust_is_mangled(demangled))
		/*
		    * Input to Rust demangling is the BFD-demangled
		    * name which it Rust-demangles in place.
		    */
		rust_demangle_sym(demangled);

	return demangled;
}