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
typedef  int UINT32 ;
typedef  int UINT16 ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */

UINT32 STREAM_TO_UINT32_f(CHAR* p, UINT16 offset)
{
	return (UINT32)((UINT32)((UINT32)
		(*(p + offset + 3)) << 24) + (UINT32)((UINT32)
		(*(p + offset + 2)) << 16) + (UINT32)((UINT32)
		(*(p + offset + 1)) << 8) + (UINT32)(*(p + offset)));
}