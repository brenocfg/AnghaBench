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
struct matrox_pll_cache {unsigned int valid; TYPE_1__* data; } ;
struct matrox_fb_info {int dummy; } ;
struct TYPE_3__ {unsigned int mnp_key; unsigned int mnp_value; } ;

/* Variables and functions */
 unsigned int G450_MNP_FREQBITS ; 
 int NO_MORE_MNP ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int g450_checkcache(struct matrox_fb_info *minfo,
			   struct matrox_pll_cache *ci, unsigned int mnp_key)
{
	unsigned int i;
	
	mnp_key &= G450_MNP_FREQBITS;
	for (i = 0; i < ci->valid; i++) {
		if (ci->data[i].mnp_key == mnp_key) {
			unsigned int mnp;
			
			mnp = ci->data[i].mnp_value;
			if (i) {
				memmove(ci->data + 1, ci->data, i * sizeof(*ci->data));
				ci->data[0].mnp_key = mnp_key;
				ci->data[0].mnp_value = mnp;
			}
			return mnp;
		}
	}
	return NO_MORE_MNP;
}