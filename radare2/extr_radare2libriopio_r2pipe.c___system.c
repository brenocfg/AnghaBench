#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmt ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  R2P (TYPE_1__*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r2pipe_read (int /*<<< orphan*/ ) ; 
 int r2pipe_write (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *__system(RIO *io, RIODesc *fd, const char *msg) {
	char fmt[4096];
	int rv, rescount = -1;
	char *res, *r;
	if (!fd || !fd->data) {
		return NULL;
	}
	snprintf (fmt, sizeof (fmt), "{\"op\":\"system\",\"cmd\":\"%s\"}", msg);
	rv = r2pipe_write (R2P (fd), fmt);
	if (rv < 1) {
		eprintf ("r2pipe_write: error\n");
		return NULL;
	}
	res = r2pipe_read (R2P (fd));
	//eprintf ("%s\n", res);
	/* TODO: parse json back */
	r = strstr (res, "result");
	if (r) {
		rescount = atoi (r + 6 + 1);
		eprintf ("RESULT %d\n", rescount);
	}
	free (res);
	return NULL;
}