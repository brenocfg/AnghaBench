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
struct nft_traceinfo {int type; TYPE_1__* verdict; } ;
struct TYPE_2__ {int code; } ;

/* Variables and functions */
#define  NFT_GOTO 131 
#define  NFT_JUMP 130 
#define  NFT_TRACETYPE_RETURN 129 
#define  NFT_TRACETYPE_RULE 128 

__attribute__((used)) static bool nft_trace_have_verdict_chain(struct nft_traceinfo *info)
{
	switch (info->type) {
	case NFT_TRACETYPE_RETURN:
	case NFT_TRACETYPE_RULE:
		break;
	default:
		return false;
	}

	switch (info->verdict->code) {
	case NFT_JUMP:
	case NFT_GOTO:
		break;
	default:
		return false;
	}

	return true;
}