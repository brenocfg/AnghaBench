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
typedef  long int32 ;

/* Variables and functions */
 int UINT64CONST (int) ; 
 int _dorand48 (unsigned short*) ; 

long
pg_jrand48(unsigned short xseed[3])
{
	uint64		x = _dorand48(xseed);

	return (int32) ((x >> 16) & UINT64CONST(0xFFFFFFFF));
}