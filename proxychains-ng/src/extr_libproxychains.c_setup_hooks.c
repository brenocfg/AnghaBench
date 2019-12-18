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

/* Variables and functions */
 int /*<<< orphan*/  SETUP_SYM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xnet_connect ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  connect ; 
 int /*<<< orphan*/  freeaddrinfo ; 
 int /*<<< orphan*/  getaddrinfo ; 
 int /*<<< orphan*/  gethostbyaddr ; 
 int /*<<< orphan*/  gethostbyname ; 
 int /*<<< orphan*/  getnameinfo ; 
 int /*<<< orphan*/  sendto ; 

__attribute__((used)) static void setup_hooks(void) {
	SETUP_SYM(connect);
	SETUP_SYM(sendto);
	SETUP_SYM(gethostbyname);
	SETUP_SYM(getaddrinfo);
	SETUP_SYM(freeaddrinfo);
	SETUP_SYM(gethostbyaddr);
	SETUP_SYM(getnameinfo);
	SETUP_SYM(close);
#ifdef IS_SOLARIS
	SETUP_SYM(__xnet_connect);
#endif
}