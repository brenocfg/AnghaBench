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
 int CopyGetData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ pg_ntoh32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
CopyGetInt32(CopyState cstate, int32 *val)
{
	uint32		buf;

	if (CopyGetData(cstate, &buf, sizeof(buf), sizeof(buf)) != sizeof(buf))
	{
		*val = 0;				/* suppress compiler warning */
		return false;
	}
	*val = (int32) pg_ntoh32(buf);
	return true;
}