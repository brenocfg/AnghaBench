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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  n64 ;
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_hton64 (int /*<<< orphan*/ ) ; 

void
fe_sendint64(int64 i, char *buf)
{
	uint64		n64 = pg_hton64(i);

	memcpy(buf, &n64, sizeof(n64));
}