#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  opbuf ;
struct TYPE_7__ {scalar_t__ syntax; int /*<<< orphan*/  bits; } ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 scalar_t__ R_ASM_SYNTAX_ATT ; 
 scalar_t__ R_ASM_SYNTAX_INTEL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_asm_op_set_buf (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int r_file_mkstemp (char*,char**) ; 
 int /*<<< orphan*/ * r_mem_mem (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int r_sandbox_open (char*,int,int) ; 
 char* r_str_newf (char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_sys_cmdf (char*,char*,char*) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	char *ipath, *opath;
	const char *syntaxstr = "";
	int len = 0;

	int ifd = r_file_mkstemp ("r_as", &ipath);
	if (ifd == -1) {
		return -1;
	}

	int ofd = r_file_mkstemp ("r_as", &opath);
	if (ofd == -1) {
		free (ipath);
		close (ifd);
		return -1;
	}

	if (a->syntax == R_ASM_SYNTAX_INTEL) {
		syntaxstr = ".intel_syntax noprefix\n";
	}

	if (a->syntax == R_ASM_SYNTAX_ATT) {
		syntaxstr = ".att_syntax\n";
	}

	char *asm_buf = r_str_newf (
			"%s.code%i\n" //.org 0x%"PFMT64x"\n"
			".ascii \"BEGINMARK\"\n"
			"%s\n"
			".ascii \"ENDMARK\"\n",
			syntaxstr, a->bits, buf); // a->pc ??
	write (ifd, asm_buf, strlen (asm_buf));
	close (ifd);
	free (asm_buf);

	if (!r_sys_cmdf ("as %s -o %s", ipath, opath)) {
		const ut8 *begin, *end;
		close (ofd);
// r_sys_cmdf ("cat %s", opath);
		ofd = r_sandbox_open (opath, O_BINARY|O_RDONLY, 0644);
		if (ofd < 0) {
			free (ipath);
			free (opath);
			return -1;
		}
		ut8 opbuf[512] = {0};
		len = read (ofd, opbuf, sizeof (opbuf));
		begin = r_mem_mem (opbuf, len, (const ut8*)"BEGINMARK", 9);
		end = r_mem_mem (opbuf, len, (const ut8*)"ENDMARK", 7);
		if (!begin || !end) {
			eprintf ("Cannot find water marks\n");
			len = 0;
		} else {
			len = (int)(size_t)(end - begin - 9);
			if (len > 0) {
				r_asm_op_set_buf (op, begin + 9, len);
			} else {
				len = 0;
			}
		}
	} else {
		eprintf ("Error running: as %s -o %s", ipath, opath);
		len = 0;
	}

	close (ofd);

	unlink (ipath);
	unlink (opath);
	free (ipath);
	free (opath);

	op->size = len;
	return len;
}