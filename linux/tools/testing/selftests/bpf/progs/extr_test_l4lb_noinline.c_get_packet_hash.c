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
struct packet_description {int /*<<< orphan*/  ports; int /*<<< orphan*/  src; int /*<<< orphan*/  srcv6; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CH_RINGS_SIZE ; 
 int /*<<< orphan*/  MAX_VIPS ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_2words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u32 get_packet_hash(struct packet_description *pckt,
			     bool ipv6)
{
	if (ipv6)
		return jhash_2words(jhash(pckt->srcv6, 16, MAX_VIPS),
				    pckt->ports, CH_RINGS_SIZE);
	else
		return jhash_2words(pckt->src, pckt->ports, CH_RINGS_SIZE);
}