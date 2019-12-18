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
typedef  size_t uint16_t ;
struct rs_control {struct rs_codec* codec; } ;
struct rs_codec {size_t* alpha_to; size_t* index_of; int nroots; int prim; int fcr; } ;

/* Variables and functions */
 size_t rs_modnn (struct rs_codec*,size_t) ; 

__attribute__((used)) static void compute_syndrome(struct rs_control *rsc, uint16_t *data,
				int len, uint16_t *syn)
{
	struct rs_codec *rs = rsc->codec;
	uint16_t *alpha_to = rs->alpha_to;
	uint16_t *index_of = rs->index_of;
	int nroots = rs->nroots;
	int prim = rs->prim;
	int fcr = rs->fcr;
	int i, j;

	/* Calculating syndrome */
	for (i = 0; i < nroots; i++) {
		syn[i] = data[0];
		for (j = 1; j < len; j++) {
			if (syn[i] == 0) {
				syn[i] = data[j];
			} else {
				syn[i] = data[j] ^
					alpha_to[rs_modnn(rs, index_of[syn[i]]
						+ (fcr + i) * prim)];
			}
		}
	}

	/* Convert to index form */
	for (i = 0; i < nroots; i++)
		syn[i] = rs->index_of[syn[i]];
}