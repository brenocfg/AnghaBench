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
typedef  int /*<<< orphan*/  u32 ;
struct taskstats {int dummy; } ;

/* Variables and functions */
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t taskstats_packet_size(void)
{
	size_t size;

	size = nla_total_size(sizeof(u32)) +
		nla_total_size_64bit(sizeof(struct taskstats)) +
		nla_total_size(0);

	return size;
}