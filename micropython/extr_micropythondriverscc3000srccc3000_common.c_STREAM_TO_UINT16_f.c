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
typedef  int UINT16 ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */

UINT16 STREAM_TO_UINT16_f(CHAR* p, UINT16 offset)
{
	return (UINT16)((UINT16)((UINT16)
		(*(p + offset + 1)) << 8) + (UINT16)(*(p + offset)));
}