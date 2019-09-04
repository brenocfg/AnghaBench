#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_10__ {scalar_t__ sa_family; } ;
struct TYPE_12__ {TYPE_2__ sa_inet; TYPE_4__ sa; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_9__ {scalar_t__ sa_family; } ;
struct TYPE_11__ {TYPE_1__ sa_inet; TYPE_3__ sa; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_UNIX ; 
 TYPE_6__* allowed_clients ; 
 TYPE_5__ client_sa ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fcgi_is_allowed() {
	int i;

	if (client_sa.sa.sa_family == AF_UNIX) {
		return 1;
	}
	if (!allowed_clients) {
		return 1;
	}
	if (client_sa.sa.sa_family == AF_INET) {
		for (i = 0; allowed_clients[i].sa.sa_family ; i++) {
			if (allowed_clients[i].sa.sa_family == AF_INET
				&& !memcmp(&client_sa.sa_inet.sin_addr, &allowed_clients[i].sa_inet.sin_addr, 4)) {
				return 1;
			}
		}
	}
#ifdef HAVE_IPV6
	if (client_sa.sa.sa_family == AF_INET6) {
		for (i = 0; allowed_clients[i].sa.sa_family ; i++) {
			if (allowed_clients[i].sa.sa_family == AF_INET6
				&& !memcmp(&client_sa.sa_inet6.sin6_addr, &allowed_clients[i].sa_inet6.sin6_addr, 12)) {
				return 1;
			}
#ifdef IN6_IS_ADDR_V4MAPPED
			if (allowed_clients[i].sa.sa_family == AF_INET
			    && IN6_IS_ADDR_V4MAPPED(&client_sa.sa_inet6.sin6_addr)
				&& !memcmp(((char *)&client_sa.sa_inet6.sin6_addr)+12, &allowed_clients[i].sa_inet.sin_addr, 4)) {
				return 1;
			}
#endif
		}
	}
#endif

	return 0;
}