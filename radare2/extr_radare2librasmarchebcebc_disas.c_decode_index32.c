#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
struct TYPE_3__ {int a_width; int n; int c; int /*<<< orphan*/  sign; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ebc_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBC_INDEX32 ; 
 int /*<<< orphan*/  EBC_INDEX_MINUS ; 
 int /*<<< orphan*/  EBC_INDEX_PLUS ; 
 int EBC_NTH_BIT (int) ; 
 int EBC_N_BIT_MASK (int) ; 

__attribute__((used)) static int decode_index32(const ut8 *data, ebc_index_t *index) {
	ut32 tmp = *(ut32*)data;
	index->type = EBC_INDEX32;
	index->sign = tmp & EBC_NTH_BIT(31) ? EBC_INDEX_PLUS : EBC_INDEX_MINUS;
	index->a_width = ((tmp >> 28) & EBC_N_BIT_MASK(2)) * 4;
	index->n = tmp & EBC_N_BIT_MASK(index->a_width);
	index->c = (tmp >> index->a_width) & EBC_N_BIT_MASK(28 - index->a_width);
	return 0;
}