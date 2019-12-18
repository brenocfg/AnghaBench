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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RSocket ;

/* Variables and functions */
 int __socket_slurp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int atoi (char const*) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_socket_close (int /*<<< orphan*/ *) ; 
 int r_socket_read_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* r_str_casestr (char*,char*) ; 

__attribute__((used)) static char *r_socket_http_answer (RSocket *s, int *code, int *rlen) {
	r_return_val_if_fail (s, NULL);
	const char *p;
	int ret, len = 0, bufsz = 32768, delta = 0;
	char *dn, *buf = calloc (1, bufsz + 32); // XXX: use r_buffer here
	if (!buf) {
		return NULL;
	}
	char *res = NULL;
	int olen = __socket_slurp (s, (ut8*)buf, bufsz);
	if ((dn = (char*)r_str_casestr (buf, "\n\n"))) {
		delta += 2;
	} else if ((dn = (char*)r_str_casestr (buf, "\r\n\r\n"))) {
		delta += 4;
	} else {
		goto fail;
	}

	olen -= delta;
	*dn = 0; // chop headers
	/* Parse Len */
	p = r_str_casestr (buf, "Content-Length: ");
	if (p) {
		len = atoi (p + 16);
	} else {
		len = olen - (dn - buf);
	}
	if (len > 0) {
		if (len > olen) {
			res = malloc (len + 2);
			memcpy (res, dn + delta, olen);
			do {
				ret = r_socket_read_block (s, (ut8*) res + olen, len - olen);
				if (ret < 1) {
					break;
				}
				olen += ret;
			} while (olen < len);
			res[len] = 0;
		} else {
			res = malloc (len + 1);
			if (res) {
				memcpy (res, dn + delta, len);
				res[len] = 0;
			}
		}
	} else {
		res = NULL;
	}
fail:
	free (buf);
// is 's' free'd? isn't this going to cause a double free?
	r_socket_close (s);
	if (rlen) {
		*rlen = len;
	}
	return res;
}