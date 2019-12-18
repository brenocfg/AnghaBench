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
struct TYPE_3__ {char** b; size_t y; int x; int* blen; int* bsize; } ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
 int R_MAX (int,int) ; 
 int __getUtf8Length2 (char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static bool __expandLine(RConsCanvas *c, int real_len, int utf8_len) {
	if (real_len == 0) {
		return true;
	}
	int buf_utf8_len = __getUtf8Length2 (c->b[c->y] + c->x, utf8_len, c->blen[c->y] - c->x);
	int goback = R_MAX (0, (buf_utf8_len - utf8_len));
	int padding = (real_len - utf8_len) - goback;

	if (padding) {
		if (padding > 0 && c->blen[c->y] + padding > c->bsize[c->y]) {
			int newsize = R_MAX (c->bsize[c->y] * 1.5, c->blen[c->y] + padding);
			char * newline = realloc (c->b[c->y], sizeof (*c->b[c->y])*(newsize));
			if (!newline) {
				return false;
			}
			memset (newline + c->bsize[c->y], 0, newsize - c->bsize[c->y]);
			c->b[c->y] = newline;
			c->bsize[c->y] = newsize;
		}
		int size = R_MAX (c->blen[c->y] - c->x - goback, 0);
		char *start = c->b[c->y] + c->x + goback;
		char *tmp = malloc (size);
		if (!tmp) {
			return false;
		}
		memcpy (tmp, start, size);
		if (padding < 0) {
			int lap = R_MAX (0, c->b[c->y] - (start + padding));
			memcpy (start + padding + lap,  tmp + lap, size - lap);
			free (tmp);
			c->blen[c->y] += padding;
			return true;
		}
		memcpy (start + padding, tmp, size);
		free (tmp);
		c->blen[c->y] += padding;
	}
	return true;
}