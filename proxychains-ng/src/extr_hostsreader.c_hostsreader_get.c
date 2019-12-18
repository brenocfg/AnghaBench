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
struct hostsreader {char* ip; char* name; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ isnumericipv4 (char*) ; 
 scalar_t__ isspace (char) ; 

int hostsreader_get(struct hostsreader *ctx, char* buf, size_t bufsize) {
	while(1) {
		if(!fgets(buf, bufsize, ctx->f)) return 0;
		if(*buf == '#') continue;
		char *p = buf;
		size_t l = bufsize;
		ctx->ip = p;
		while(*p && !isspace(*p) && l) {
			p++;
			l--;
		}
		if(!l || !*p || p == ctx->ip) continue;
		*p = 0;
		p++;
		while(*p && isspace(*p) && l) {
			p++;
			l--;
		}
		if(!l || !*p) continue;
		ctx->name = p;
		while(*p && !isspace(*p) && l) {
			p++;
			l--;
		}
		if(!l || !*p) continue;
		*p = 0;
		if(isnumericipv4(ctx->ip)) return 1;
	}
}