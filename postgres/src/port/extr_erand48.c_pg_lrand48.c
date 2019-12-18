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
typedef  int uint64 ;

/* Variables and functions */
 int UINT64CONST (int) ; 
 int _dorand48 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rand48_seed ; 

long
pg_lrand48(void)
{
	uint64		x = _dorand48(_rand48_seed);

	return (x >> 17) & UINT64CONST(0x7FFFFFFF);
}