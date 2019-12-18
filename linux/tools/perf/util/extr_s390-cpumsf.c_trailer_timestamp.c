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
typedef  int /*<<< orphan*/  ts ;
struct hws_trailer_entry {int /*<<< orphan*/ * timestamp; } ;

/* Variables and functions */
 unsigned long long be64toh (unsigned long long) ; 
 int /*<<< orphan*/  memcpy (unsigned long long*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long long trailer_timestamp(struct hws_trailer_entry *te,
					    int idx)
{
	/* te->t set: TOD in STCKE format, bytes 8-15
	 * to->t not set: TOD in STCK format, bytes 0-7
	 */
	unsigned long long ts;

	memcpy(&ts, &te->timestamp[idx], sizeof(ts));
	return be64toh(ts);
}