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
typedef  int rs_proxyType ;

/* Variables and functions */
#define  RS_PT_HTTP 130 
#define  RS_PT_SOCKS4 129 
#define  RS_PT_SOCKS5 128 
 int atoi (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int proxy_from_string(const char *proxystring,
	char *type_buf,
	char* host_buf,
	int *port_n,
	char *user_buf,
	char* pass_buf)
{
	const char* p;
	rs_proxyType proxytype;

	size_t next_token = 6, ul = 0, pl = 0, hl;
	if(!proxystring[0] || !proxystring[1] || !proxystring[2] || !proxystring[3] || !proxystring[4] || !proxystring[5]) goto inv_string;
	if(*proxystring == 's') {
		switch(proxystring[5]) {
			case '5': proxytype = RS_PT_SOCKS5; break;
			case '4': proxytype = RS_PT_SOCKS4; break;
			default: goto inv_string;
		}
	} else if(*proxystring == 'h') {
		proxytype = RS_PT_HTTP;
		next_token = 4;
	} else goto inv_string;
	if(
	   proxystring[next_token++] != ':' ||
	   proxystring[next_token++] != '/' ||
	   proxystring[next_token++] != '/') goto inv_string;
	const char *at = strrchr(proxystring+next_token, '@');
	if(at) {
		if(proxytype == RS_PT_SOCKS4)
			return 0;
		p = strchr(proxystring+next_token, ':');
		if(!p || p >= at) goto inv_string;
		const char *u = proxystring+next_token;
		ul = p-u;
		p++;
		pl = at-p;
		if(proxytype == RS_PT_SOCKS5 && (ul > 255 || pl > 255))
			return 0;
		memcpy(user_buf, u, ul);
		user_buf[ul]=0;
		memcpy(pass_buf, p, pl);
		pass_buf[pl]=0;
		next_token += 2+ul+pl;
	} else {
		user_buf[0]=0;
		pass_buf[0]=0;
	}
	const char* h = proxystring+next_token;
	p = strchr(h, ':');
	if(!p) goto inv_string;
	hl = p-h;
	if(hl > 255)
		return 0;
	memcpy(host_buf, h, hl);
	host_buf[hl]=0;
	*port_n = atoi(p+1);
	switch(proxytype) {
		case RS_PT_SOCKS4:
			strcpy(type_buf, "socks4");
			break;
		case RS_PT_SOCKS5:
			strcpy(type_buf, "socks5");
			break;
		case RS_PT_HTTP:
			strcpy(type_buf, "http");
			break;
		default:
			return 0;
	}
	return 1;
inv_string:
	return 0;
}