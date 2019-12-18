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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {char* filename; scalar_t__ line_num; struct TYPE_6__* prev; } ;
struct TYPE_5__ {int /*<<< orphan*/  nb_errors; scalar_t__ warn_error; int /*<<< orphan*/  error_opaque; int /*<<< orphan*/  (* error_func ) (int /*<<< orphan*/ ,char*) ;TYPE_2__** include_stack_ptr; TYPE_2__** include_stack; } ;
typedef  TYPE_1__ TCCState ;
typedef  TYPE_2__ BufferedFile ;

/* Variables and functions */
 TYPE_2__* file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat_printf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcat_vprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void error1(TCCState *s1, int is_warning, const char *fmt, va_list ap)
{
	char buf[2048];
	BufferedFile **pf, *f;

	buf[0] = '\0';
	/* use upper file if inline ":asm:" or token ":paste:" */
	for (f = file; f && f->filename[0] == ':'; f = f->prev) {
		;
	}
	if (f) {
		for (pf = s1->include_stack; pf < s1->include_stack_ptr; pf++) {
			strcat_printf (buf, sizeof(buf), "In file included from %s:%d:\n",
				(*pf)->filename, (*pf)->line_num);
		}
		if (f->line_num > 0) {
			strcat_printf (buf, sizeof(buf), "%s:%d: ",
				f->filename, f->line_num);
		} else {
			strcat_printf (buf, sizeof(buf), "%s: ",
				f->filename);
		}
	} else {
		strcat_printf (buf, sizeof(buf), "tcc: ");
	}
	if (is_warning) {
		strcat_printf (buf, sizeof(buf), "warning: ");
	} else {
		strcat_printf (buf, sizeof(buf), "error: ");
	}
	strcat_vprintf (buf, sizeof(buf), fmt, ap);

	if (!s1->error_func) {
		/* default case: stderr */
		fprintf (stderr, "%s\n", buf);
	} else {
		s1->error_func (s1->error_opaque, buf);
	}
	if (!is_warning || s1->warn_error) {
		s1->nb_errors++;
	}
}