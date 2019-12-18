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
struct hostsreader {char* ip; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostsreader_close (struct hostsreader*) ; 
 scalar_t__ hostsreader_get (struct hostsreader*,char*,size_t) ; 
 int /*<<< orphan*/  hostsreader_open (struct hostsreader*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

char* hostsreader_get_ip_for_name(const char* name, char* buf, size_t bufsize) {
	struct hostsreader ctx;
	char *res = 0;
	if(!hostsreader_open(&ctx)) return 0;
	while(hostsreader_get(&ctx, buf, bufsize)) {
		if(!strcmp(ctx.name, name)) {
			res = ctx.ip;
			break;
		}
	}
	hostsreader_close(&ctx);
	return res;
}