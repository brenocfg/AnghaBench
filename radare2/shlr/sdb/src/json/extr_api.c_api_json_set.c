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
struct TYPE_3__ {char* p; int f; int t; } ;
typedef  TYPE_1__ Rangstr ;

/* Variables and functions */
 int WLEN (int) ; 
 TYPE_1__ json_get (char const*,char const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *api_json_set (const char *s, const char *k, const char *v) {
	const char *beg[3];
	const char *end[3];
	int idx, len[3];
	char *str = NULL;
	Rangstr rs = json_get (s, k);
	if (!rs.p) {
		return NULL;
	}
#define WLEN(x) (int)(size_t)(end[x]-beg[x])

	beg[0] = s;
	end[0] = rs.p + rs.f;
	len[0] = WLEN (0);

	beg[1] = v;
	end[1] = v + strlen (v);
	len[1] = WLEN (1);

	beg[2] = rs.p + rs.t;
	end[2] = s + strlen (s);
	len[2] = WLEN (2);

	str = malloc (len[0]+len[1]+len[2]+1);
	if (!str) {
		return NULL;
	}
	idx = len[0];
	memcpy (str, beg[0], idx);
	memcpy (str+idx, beg[1], len[1]);
	idx += len[1];
	memcpy (str+idx, beg[2], len[2]);
	str[idx+len[2]] = 0;
	return str;
}