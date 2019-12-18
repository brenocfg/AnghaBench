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
struct cEnv_t {char* CC; char* JMP; char* OBJCOPY; char* FMT; char* CFLAGS; char* LDFLAGS; char const* TRIPLET; char* TEXT; void* SFLIBPATH; void* SHDR; } ;

/* Variables and functions */
 struct cEnv_t* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isXNU (char const*) ; 
 scalar_t__ r_egg_Cfile_armOrMips (char const*) ; 
 scalar_t__ r_egg_Cfile_check_cEnv (struct cEnv_t*) ; 
 int /*<<< orphan*/  r_egg_Cfile_free_cEnv (struct cEnv_t*) ; 
 char* r_egg_Cfile_getCompiler () ; 
 void* r_str_newf (char*,char const*,...) ; 
 char* r_sys_cmd_strf (char*) ; 
 void* r_sys_getenv (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static struct cEnv_t* r_egg_Cfile_set_cEnv(const char *arch, const char *os, int bits) {
	struct cEnv_t *cEnv = calloc (1, sizeof (struct cEnv_t));
	bool use_clang;
	char *buffer = NULL;
	char *output = NULL;

	if (!cEnv) {
		return NULL;
	}

	if (!(cEnv->CC = r_egg_Cfile_getCompiler())) {
		goto fail;
	}

	cEnv->SFLIBPATH = r_sys_getenv ("SFLIBPATH");
	if (!cEnv->SFLIBPATH) {
		output = r_sys_cmd_strf ("r2 -hh | grep INCDIR | awk '{print $2}'");
		if (!output || (output[0] == '\0')) {
			eprintf ("Cannot find SFLIBPATH env var.\n"
		  		 "Please define it, or fix r2 installation.\n");
			goto fail;
		}

		output[strlen (output) - 1] = '\0'; // strip the ending '\n'
		if (!(cEnv->SFLIBPATH = r_str_newf ("%s/sflib", output))) {
			goto fail;
		}
	}

	cEnv->JMP = r_egg_Cfile_armOrMips (arch) ? "b" : "jmp";

	// TODO: Missing -Os .. caused some rip-relative LEA to be MOVQ on PIE in CLANG.. so sad
	if (isXNU (os)) {
		cEnv->OBJCOPY = "gobjcopy";
		cEnv->FMT = "mach0";
		if (!strcmp (arch, "x86")) {
			if (bits == 32) {
				cEnv->CFLAGS = strdup ("-arch i386 -fPIC -fPIE");
				cEnv->LDFLAGS = strdup ("-arch i386 -shared -c -fPIC -fPIE -pie");
			} else {
				cEnv->CFLAGS = strdup ("-arch x86_64 -fPIC -fPIE");
				cEnv->LDFLAGS = strdup ("-arch x86_64 -shared -c -fPIC -fPIE -pie");
			}
		} else {
			cEnv->CFLAGS = strdup ("-shared -c -fPIC -pie -fPIE");
			cEnv->LDFLAGS = strdup ("-shared -c -fPIC -pie -fPIE");
		}
		cEnv->SHDR = r_str_newf ("\n.text\n%s _main\n", cEnv->JMP);
	} else {
		cEnv->OBJCOPY = "objcopy";
		cEnv->FMT = "elf";
		cEnv->SHDR = r_str_newf ("\n.section .text\n.globl  main\n"
				   "// .type   main, @function\n%s main\n", cEnv->JMP);
		if (!strcmp (arch, "x86")) {
			if (bits == 32) {
				cEnv->CFLAGS = strdup ("-fPIC -fPIE -pie -fpic -m32");
				cEnv->LDFLAGS = strdup ("-fPIC -fPIE -pie -fpic -m32");
			} else {
				cEnv->CFLAGS = strdup ("-fPIC -fPIE -pie -fpic -m64");
				cEnv->LDFLAGS = strdup ("-fPIC -fPIE -pie -fpic -m64");
			}
		} else {
			cEnv->CFLAGS = strdup ("-fPIC -fPIE -pie -fpic -nostartfiles");
			cEnv->LDFLAGS = strdup ("-fPIC -fPIE -pie -fpic -nostartfiles");
		}
	}

	cEnv->TRIPLET = r_str_newf ("%s-%s-%d", os, arch, bits);

	if (!strcmp (os, "windows")) {
		cEnv->TEXT = ".text";
		cEnv->FMT = "pe";
	} else if (isXNU(os)) {
		//cEnv->TEXT = "0.__TEXT.__text";
		cEnv->TEXT = "0..__text";
	} else {
		cEnv->TEXT = ".text";
	}

	use_clang = false;
	if (!strcmp (cEnv->TRIPLET, "darwin-arm-64")) {
		free (cEnv->CC);
		cEnv->CC = strdup ("xcrun --sdk iphoneos gcc -arch arm64 -miphoneos-version-min=0.0");
		use_clang = true;
		cEnv->TEXT = "0.__TEXT.__text";
	} else if (!strcmp (cEnv->TRIPLET, "darwin-arm-32")) {
		free (cEnv->CC);
		cEnv->CC = strdup ("xcrun --sdk iphoneos gcc -arch armv7 -miphoneos-version-min=0.0");
		use_clang = true;
		cEnv->TEXT = "0.__TEXT.__text";
	}

	buffer = r_str_newf ("%s -fno-stack-protector -nostdinc -include '%s'/'%s'/sflib.h",
	  		cEnv->CFLAGS, cEnv->SFLIBPATH, cEnv->TRIPLET);
	if (!buffer) {
		goto fail;
	}
	free (cEnv->CFLAGS);
	cEnv->CFLAGS = strdup (buffer);

	if (use_clang) {
		free (buffer);
		buffer = r_str_newf ("%s -fomit-frame-pointer"
		  		" -fno-zero-initialized-in-bss", cEnv->CFLAGS);
		if (!buffer) {
			goto fail;
		}
		free (cEnv->CFLAGS);
		cEnv->CFLAGS = strdup (buffer);
	} else {
		free (buffer);
		buffer = r_str_newf ("%s -z execstack -fomit-frame-pointer"
				" -finline-functions -fno-zero-initialized-in-bss", cEnv->CFLAGS);
		if (!buffer) {
			goto fail;
		}
		free (cEnv->CFLAGS);
		cEnv->CFLAGS = strdup (buffer);
	}
	free (buffer);
	buffer = r_str_newf ("%s -nostdlib", cEnv->LDFLAGS);
	if (!buffer) {
		goto fail;
	}
	free (cEnv->LDFLAGS);
	cEnv->LDFLAGS = strdup (buffer);

	if (r_egg_Cfile_check_cEnv (cEnv)) {
		eprintf ("Error with cEnv allocation!\n");
		goto fail;
	}

	free (buffer);
	free (output);
	return cEnv;

fail:
	free (buffer);
	free (output);
	r_egg_Cfile_free_cEnv (cEnv);
	return NULL;
}