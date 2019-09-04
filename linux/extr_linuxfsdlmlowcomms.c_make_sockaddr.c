#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {char sin_zero; void* sin_port; } ;
struct TYPE_2__ {scalar_t__ ss_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 TYPE_1__** dlm_local_addr ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void make_sockaddr(struct sockaddr_storage *saddr, uint16_t port,
			  int *addr_len)
{
	saddr->ss_family =  dlm_local_addr[0]->ss_family;
	if (saddr->ss_family == AF_INET) {
		struct sockaddr_in *in4_addr = (struct sockaddr_in *)saddr;
		in4_addr->sin_port = cpu_to_be16(port);
		*addr_len = sizeof(struct sockaddr_in);
		memset(&in4_addr->sin_zero, 0, sizeof(in4_addr->sin_zero));
	} else {
		struct sockaddr_in6 *in6_addr = (struct sockaddr_in6 *)saddr;
		in6_addr->sin6_port = cpu_to_be16(port);
		*addr_len = sizeof(struct sockaddr_in6);
	}
	memset((char *)saddr + *addr_len, 0, sizeof(struct sockaddr_storage) - *addr_len);
}