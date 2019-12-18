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
struct TYPE_3__ {char* lbuf; int lbuf_n; int lbuf_s; } ;
typedef  TYPE_1__ SppBuf ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

void lbuf_strcat(SppBuf *dst, char *src) {
	int len = strlen (src);
	char *nbuf;
	if (!dst->lbuf || (len + dst->lbuf_n) > dst->lbuf_s) {
		nbuf = realloc (dst->lbuf, dst->lbuf_s << 1);
		if (!nbuf) {
			fprintf (stderr, "Out of memory.\n");
			return;
		}
		dst->lbuf = nbuf;
	}
	memcpy (dst->lbuf + dst->lbuf_n, src, len + 1);
	dst->lbuf_n += len;
}