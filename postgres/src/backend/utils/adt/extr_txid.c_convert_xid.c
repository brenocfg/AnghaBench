#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int txid ;
struct TYPE_3__ {int last_xid; scalar_t__ epoch; } ;
typedef  TYPE_1__ TxidEpoch ;
typedef  int TransactionId ;

/* Variables and functions */
 scalar_t__ TransactionIdFollows (int,int) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int) ; 
 scalar_t__ TransactionIdPrecedes (int,int) ; 

__attribute__((used)) static txid
convert_xid(TransactionId xid, const TxidEpoch *state)
{
	uint64		epoch;

	/* return special xid's as-is */
	if (!TransactionIdIsNormal(xid))
		return (txid) xid;

	/* xid can be on either side when near wrap-around */
	epoch = (uint64) state->epoch;
	if (xid > state->last_xid &&
		TransactionIdPrecedes(xid, state->last_xid))
		epoch--;
	else if (xid < state->last_xid &&
			 TransactionIdFollows(xid, state->last_xid))
		epoch++;

	return (epoch << 32) | xid;
}