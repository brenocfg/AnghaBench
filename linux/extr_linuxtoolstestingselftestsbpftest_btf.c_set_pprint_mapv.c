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
typedef  int uint32_t ;
struct pprint_mapv {int ui32; int si32; int unused_bits2a; int bits28; int unused_bits2b; int ui64; int aenum; } ;

/* Variables and functions */

__attribute__((used)) static void set_pprint_mapv(struct pprint_mapv *v, uint32_t i)
{
	v->ui32 = i;
	v->si32 = -i;
	v->unused_bits2a = 3;
	v->bits28 = i;
	v->unused_bits2b = 3;
	v->ui64 = i;
	v->aenum = i & 0x03;
}