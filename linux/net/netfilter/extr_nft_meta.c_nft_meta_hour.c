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
typedef  scalar_t__ u32 ;
struct tm {int tm_hour; int tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */
 int NFT_META_SECS_PER_HOUR ; 
 int NFT_META_SECS_PER_MINUTE ; 
 int /*<<< orphan*/  time64_to_tm (unsigned long,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static u32 nft_meta_hour(unsigned long secs)
{
	struct tm tm;

	time64_to_tm(secs, 0, &tm);

	return tm.tm_hour * NFT_META_SECS_PER_HOUR
		+ tm.tm_min * NFT_META_SECS_PER_MINUTE
		+ tm.tm_sec;
}