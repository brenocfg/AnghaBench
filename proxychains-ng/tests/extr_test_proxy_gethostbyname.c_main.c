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
struct hostent {int dummy; } ;
struct gethostbyname_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printhostent (struct hostent*) ; 
 struct hostent* proxy_gethostbyname (char*,struct gethostbyname_data*) ; 

int main(int argc, char**argv) {
	struct hostent* ret;
	struct gethostbyname_data data;
	if(argc == 1) return 1;
	ret = proxy_gethostbyname(argv[1], &data);
	if(ret) printhostent(ret);
	return 0;
}