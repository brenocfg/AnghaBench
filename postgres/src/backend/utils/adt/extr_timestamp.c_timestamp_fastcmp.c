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
typedef  int /*<<< orphan*/  Timestamp ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 int timestamp_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
timestamp_fastcmp(Datum x, Datum y, SortSupport ssup)
{
	Timestamp	a = DatumGetTimestamp(x);
	Timestamp	b = DatumGetTimestamp(y);

	return timestamp_cmp_internal(a, b);
}