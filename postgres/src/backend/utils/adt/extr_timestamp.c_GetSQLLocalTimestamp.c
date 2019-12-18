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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustTimestampForTypmod (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTransactionStartTimestamp () ; 
 int /*<<< orphan*/  timestamptz2timestamp (int /*<<< orphan*/ ) ; 

Timestamp
GetSQLLocalTimestamp(int32 typmod)
{
	Timestamp	ts;

	ts = timestamptz2timestamp(GetCurrentTransactionStartTimestamp());
	if (typmod >= 0)
		AdjustTimestampForTypmod(&ts, typmod);
	return ts;
}