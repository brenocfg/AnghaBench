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
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static DWORD ld_dword (const BYTE* ptr)	/* Load a 4-byte little-endian word */
{
	DWORD rv;

	rv = ptr[3];
	rv = rv << 8 | ptr[2];
	rv = rv << 8 | ptr[1];
	rv = rv << 8 | ptr[0];
	return rv;
}