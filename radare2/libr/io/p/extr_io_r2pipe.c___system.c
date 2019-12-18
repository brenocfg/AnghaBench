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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  R2P (int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 char* pj_string (int /*<<< orphan*/ *) ; 
 char* r2pipe_read (int /*<<< orphan*/ ) ; 
 int r2pipe_write (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *__system(RIO *io, RIODesc *fd, const char *msg) {
	r_return_val_if_fail (io && fd && msg, NULL);
	PJ *pj = pj_new ();
	pj_o (pj);
	pj_ks (pj, "op", "system");
	pj_ks (pj, "cmd", msg);
	pj_end (pj);
	const char *fmt = pj_string (pj);
	int rv = r2pipe_write (R2P (fd), fmt);
	pj_free (pj);
	if (rv < 1) {
		eprintf ("r2pipe_write: error\n");
		return NULL;
	}
	char *res = r2pipe_read (R2P (fd));
	//eprintf ("%s\n", res);
	/* TODO: parse json back */
	char *r = strstr (res, "result");
	if (r) {
		int rescount = atoi (r + 6 + 1);
		eprintf ("RESULT %d\n", rescount);
	}
	free (res);
	return NULL;
}