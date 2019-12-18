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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int pc_getnameinfo (void const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int getnameinfo(const void *sa, socklen_t salen, 
                   char *host, socklen_t hostlen, char *serv, 
                   socklen_t servlen, int flags) {
	return pc_getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
}