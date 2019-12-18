#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cout; int /*<<< orphan*/ * fout; } ;
typedef  TYPE_1__ Output ;

/* Variables and functions */
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_new (char*) ; 
 int spp_run (char*,TYPE_1__*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *spp_run_str(char *buf, int *rv) {
	char *b;
	Output tmp;
	tmp.fout = NULL;
	tmp.cout = r_strbuf_new ("");
	int rc = spp_run (buf, &tmp);
	b = strdup (r_strbuf_get (tmp.cout));
	r_strbuf_free (tmp.cout);
	if (rv) {
		*rv = rc;
	}
	return b;
}