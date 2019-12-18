#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bits; int alacarte_link; int nocommon; int char_is_unsigned; int leading_underscore; int seg_size; int /*<<< orphan*/  include_stack; int /*<<< orphan*/  include_stack_ptr; int /*<<< orphan*/  output_type; void* os; void* arch; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 int /*<<< orphan*/  MACRO_OBJ ; 
 int /*<<< orphan*/  TCC_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  TCC_VERSION ; 
 int /*<<< orphan*/  TOK___DATE__ ; 
 int /*<<< orphan*/  TOK___FILE__ ; 
 int /*<<< orphan*/  TOK___LINE__ ; 
 int /*<<< orphan*/  TOK___TIME__ ; 
 int /*<<< orphan*/  __FreeBSD__ ; 
 int /*<<< orphan*/  define_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preprocess_new () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*) ; 
 char* str (int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tcc_cleanup () ; 
 int /*<<< orphan*/  tcc_define_symbol (TYPE_1__*,char*,char*) ; 
 TYPE_1__* tcc_mallocz (int) ; 
 TYPE_1__* tcc_state ; 

TCCState *tcc_new(const char *arch, int bits, const char *os)
{
	TCCState *s;
	char buffer[100];
	int a, b, c;

	if (!arch || !os) {
		return NULL;
	}
	tcc_cleanup ();
	s = tcc_mallocz (sizeof(TCCState));
	if (!s) {
		return NULL;
	}
	tcc_state = s;
	s->arch = strdup (arch);
	s->bits = bits;
	s->os = strdup (os);
	s->output_type = TCC_OUTPUT_MEMORY;
	preprocess_new ();
	s->include_stack_ptr = s->include_stack;

	/* we add dummy defines for some special macros to speed up tests
	   and to have working defined() */
	define_push (TOK___LINE__, MACRO_OBJ, NULL, NULL);
	define_push (TOK___FILE__, MACRO_OBJ, NULL, NULL);
	define_push (TOK___DATE__, MACRO_OBJ, NULL, NULL);
	define_push (TOK___TIME__, MACRO_OBJ, NULL, NULL);

	/* define __TINYC__ 92X  */
	sscanf (TCC_VERSION, "%d.%d.%d", &a, &b, &c);
	sprintf (buffer, "%d", a * 10000 + b * 100 + c);
	tcc_define_symbol (s, "__TINYC__", buffer);
	tcc_define_symbol (s, "__R2TINYC__", buffer);

	/* standard defines */
	tcc_define_symbol (s, "__STDC__", NULL);
	tcc_define_symbol (s, "__STDC_VERSION__", "199901L");
	tcc_define_symbol (s, "__STDC_HOSTED__", NULL);

	/* type defines */
	tcc_define_symbol (s, "ut8", "uint8_t");
	tcc_define_symbol (s, "ut16", "uint16_t");
	tcc_define_symbol (s, "ut32", "uint32_t");
	tcc_define_symbol (s, "ut64", "uint64_t");

	tcc_define_symbol (s, "st8", "int8_t");
	tcc_define_symbol (s, "st16", "int16_t");
	tcc_define_symbol (s, "st32", "int32_t");
	tcc_define_symbol (s, "st64", "int64_t");

	/* target defines */
	if (!strncmp (arch, "x86", 3)) {
		if (bits == 32 || bits == 16) {
			tcc_define_symbol (s, "__i386__", NULL);
			tcc_define_symbol (s, "__i386", NULL);
			tcc_define_symbol (s, "i386", NULL);
		} else {
			tcc_define_symbol (s, "__x86_64__", NULL);
		}
	} else if (!strncmp (arch, "arm", 3)) {
		tcc_define_symbol (s, "__ARM_ARCH_4__", NULL);
		tcc_define_symbol (s, "__arm_elf__", NULL);
		tcc_define_symbol (s, "__arm_elf", NULL);
		tcc_define_symbol (s, "arm_elf", NULL);
		tcc_define_symbol (s, "__arm__", NULL);
		tcc_define_symbol (s, "__arm", NULL);
		tcc_define_symbol (s, "arm", NULL);
		tcc_define_symbol (s, "__APCS_32__", NULL);
	}
	// TODO: Add other architectures
	// TODO: Move that in SDB

	if (!strncmp (os, "windows", 7)) {
		tcc_define_symbol (s, "__WINDOWS__", NULL);
		if (bits == 64) {
			tcc_define_symbol (s, "_WIN64", NULL);
		}
	} else {
		tcc_define_symbol (s, "__unix__", NULL);
		tcc_define_symbol (s, "__unix", NULL);
		tcc_define_symbol (s, "unix", NULL);

		if (!strncmp (os, "linux", 5)) {
			tcc_define_symbol (s, "__linux__", NULL);
			tcc_define_symbol (s, "__linux", NULL);
		}
#define str(s) #s
		if (!strncmp (os, "freebsd", 7)) {
			tcc_define_symbol (s, "__FreeBSD__", str ( __FreeBSD__));
		}
#undef str
	}

	/* TinyCC & gcc defines */
	if (!strncmp (os, "windows", 7) && (bits == 64)) {
		tcc_define_symbol (s, "__SIZE_TYPE__", "unsigned long long");
		tcc_define_symbol (s, "__PTRDIFF_TYPE__", "long long");
	} else {
		tcc_define_symbol (s, "__SIZE_TYPE__", "unsigned long");
		tcc_define_symbol (s, "__PTRDIFF_TYPE__", "long");
	}

	if (!strncmp (os, "windows", 7)) {
		tcc_define_symbol (s, "__WCHAR_TYPE__", "unsigned short");
	} else {
		tcc_define_symbol (s, "__WCHAR_TYPE__", "int");
		/* glibc defines */
		tcc_define_symbol (s, "__REDIRECT(name, proto, alias)", "name proto __asm__(#alias)");
		tcc_define_symbol (s, "__REDIRECT_NTH(name, proto, alias)", "name proto __asm__(#alias) __THROW");
	}

	s->alacarte_link = 1;
	s->nocommon = 1;

#ifdef CHAR_IS_UNSIGNED
	s->char_is_unsigned = 1;
#endif
	/* enable this if you want symbols with leading underscore on windows: */
#if 0	/* def TCC_TARGET_PE */
	s->leading_underscore = 1;
#endif
	if (!strncmp (arch, "x86", 3)) {
		// TODO: Set it to 16 for 16bit x86
		if (bits == 32 || bits == 16) {
			s->seg_size = 32;
		}
	}
	return s;
}