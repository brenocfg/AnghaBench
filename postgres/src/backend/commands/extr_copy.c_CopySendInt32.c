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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  CopySendData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_hton32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CopySendInt32(CopyState cstate, int32 val)
{
	uint32		buf;

	buf = pg_hton32((uint32) val);
	CopySendData(cstate, &buf, sizeof(buf));
}