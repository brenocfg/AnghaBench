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
struct TYPE_3__ {int /*<<< orphan*/  (* cb_printf ) (char*,char*) ;} ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  rURL (int /*<<< orphan*/ *) ; 
 char* r_socket_http_get (char*,int*,int*) ; 
 char* r_str_newf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 

__attribute__((used)) static char *__system(RIO *io, RIODesc *fd, const char *command) {
	int code, rlen;
	char *out;
	char *url = r_str_newf ("%s/%s", rURL(fd), command);
	out = r_socket_http_get (url, &code, &rlen);
	if (out && rlen > 0) {
		io->cb_printf ("%s", out);
	}
	free (out);
	free (url);
	return NULL;
}