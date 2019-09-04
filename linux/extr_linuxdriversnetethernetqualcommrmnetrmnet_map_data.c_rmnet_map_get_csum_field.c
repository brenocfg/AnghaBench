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
struct udphdr {int /*<<< orphan*/  check; } ;
struct tcphdr {int /*<<< orphan*/  check; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 

__attribute__((used)) static __sum16 *rmnet_map_get_csum_field(unsigned char protocol,
					 const void *txporthdr)
{
	__sum16 *check = NULL;

	switch (protocol) {
	case IPPROTO_TCP:
		check = &(((struct tcphdr *)txporthdr)->check);
		break;

	case IPPROTO_UDP:
		check = &(((struct udphdr *)txporthdr)->check);
		break;

	default:
		check = NULL;
		break;
	}

	return check;
}