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
struct TYPE_2__ {int /*<<< orphan*/  ports; int /*<<< orphan*/  src; int /*<<< orphan*/  srcv6; } ;
struct packet_description {TYPE_1__ flow; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  jhash_2words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __attribute__ ((noinline))
__u32 get_packet_hash(struct packet_description *pckt,
		      bool hash_16bytes)
{
	if (hash_16bytes)
		return jhash_2words(jhash(pckt->flow.srcv6, 16, 12),
				    pckt->flow.ports, 24);
	else
		return jhash_2words(pckt->flow.src, pckt->flow.ports,
				    24);
}