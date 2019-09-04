#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char ut8 ;
struct TYPE_2__ {char* root; int /*<<< orphan*/  out; scalar_t__ encode; } ;
typedef  TYPE_1__ ForeachListUser ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* sdb_decode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_append (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int foreach_list_cb(void *user, const char *k, const char *v) {
	ForeachListUser *rlu = user;
	char *line, *root;
	int rlen, klen, vlen;
	ut8 *v2 = NULL;
	if (!rlu) {
		return 0;
	}
	root = rlu->root;
	klen = strlen (k);
	if (rlu->encode) {
		v2 = sdb_decode (v, NULL);
		if (v2) {
			v = (const char *)v2;
		}
	}
	vlen = strlen (v);
	if (root) {
		rlen = strlen (root);
		line = malloc (klen + vlen + rlen + 3);
		if (!line) {
			free (v2);
			return 0;
		}
		memcpy (line, root, rlen);
		line[rlen]='/'; /*append the '/' at the end of the namespace */
		memcpy (line + rlen + 1, k, klen);
		line[rlen + klen + 1] = '=';
		memcpy (line + rlen + klen + 2, v, vlen + 1);
	} else {
		line = malloc (klen + vlen + 2);
		if (!line) {
			free (v2);
			return 0;
		}
		memcpy (line, k, klen);
		line[klen] = '=';
		memcpy (line + klen + 1, v, vlen + 1);
	}
	strbuf_append (rlu->out, line, 1);
	free (v2);
	free (line);
	return 1;
}