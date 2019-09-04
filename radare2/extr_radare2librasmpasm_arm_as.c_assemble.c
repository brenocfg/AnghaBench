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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int bits; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  ARM32_AS ; 
 int /*<<< orphan*/  ARM64_AS ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_file_mkstemp (char*,char**) ; 
 int /*<<< orphan*/ * r_mem_mem (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int r_sandbox_open (char*,int,int) ; 
 char* r_str_newf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  r_strbuf_setbin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_sys_cmdf (char*,char*,char*,char*) ; 
 char* r_sys_getenv (char*) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	const char *bitconfig = "";
	char *ipath, *opath;
	char *as = NULL;

	int ifd = r_file_mkstemp ("r_as", &ipath);
	if (ifd == -1) {
		return -1;
	}

	int ofd = r_file_mkstemp ("r_as", &opath);
	if (ofd == -1) {
		free (ipath);
		return -1;
	}

	as = r_sys_getenv ("ARM_AS");
	if (!as || !*as) {
		free (as);
		if (a->bits == 64) {
			as = strdup (ARM64_AS);
		} else {
			as = strdup (ARM32_AS);
		}
	}
	if (a->bits == 16) {
		bitconfig = ".thumb";
	}

	char *asm_buf = r_str_newf ("%s\n" //.org 0x%"PFMT64x"\n"
			".ascii \"BEGINMARK\"\n"
			"%s\n"
			".ascii \"ENDMARK\"\n",
			bitconfig, buf); // a->pc ??
	if (asm_buf) {
		(void)write (ifd, asm_buf, strlen (asm_buf));
		(void)close (ifd);
		free (asm_buf);
	}

	int len = 0;
	if (!r_sys_cmdf ("%s %s -o %s", as, ipath, opath)) {
		const ut8 *begin, *end;
		close (ofd);
		ofd = r_sandbox_open (opath, O_BINARY|O_RDONLY, 0644);
		if (ofd < 0) {
			free (as);
			free (ipath);
			free (opath);
			return -1;
		}
		ut8 buf[4096];
		len = read (ofd, buf, sizeof (buf));
		begin = r_mem_mem (buf, len, (const ut8*)"BEGINMARK", 9);
		end = r_mem_mem (buf, len, (const ut8*)"ENDMARK", 7);
		if (!begin || !end) {
			eprintf ("Cannot find water marks\n");
			len = 0;
		} else {
			len = (int)(size_t)(end - begin - 9);
			if (len > 0) {
				r_strbuf_setbin (&op->buf, begin + 9, len);
			} else {
				len = 0;
			}
		}
	} else {
		eprintf ("Error running: %s %s -o %s", as, ipath, opath);
		eprintf ("export PATH=~/NDK/toolchains/arm-linux*/prebuilt/darwin-arm_64/bin\n");
	}

	close (ofd);

	unlink (ipath);
	unlink (opath);
	free (ipath);
	free (opath);
	free (as);

	return op->size = len;
}