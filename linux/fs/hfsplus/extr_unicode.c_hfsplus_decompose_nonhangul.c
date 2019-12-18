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
typedef  int wchar_t ;
typedef  int u16 ;

/* Variables and functions */
 int* hfsplus_decompose_table ; 

__attribute__((used)) static u16 *hfsplus_decompose_nonhangul(wchar_t uc, int *size)
{
	int off;

	off = hfsplus_decompose_table[(uc >> 12) & 0xf];
	if (off == 0 || off == 0xffff)
		return NULL;

	off = hfsplus_decompose_table[off + ((uc >> 8) & 0xf)];
	if (!off)
		return NULL;

	off = hfsplus_decompose_table[off + ((uc >> 4) & 0xf)];
	if (!off)
		return NULL;

	off = hfsplus_decompose_table[off + (uc & 0xf)];
	*size = off & 3;
	if (*size == 0)
		return NULL;
	return hfsplus_decompose_table + (off / 4);
}