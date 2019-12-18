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
typedef  int u4byte ;
struct TYPE_3__ {int k_len; int* e_key; } ;
typedef  TYPE_1__ rijndael_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  f_lround (int*,int*,int*) ; 
 int /*<<< orphan*/  f_nround (int*,int*,int*) ; 
 int io_swap (int const) ; 

void
rijndael_encrypt(rijndael_ctx *ctx, const u4byte *in_blk, u4byte *out_blk)
{
	u4byte		k_len = ctx->k_len;
	u4byte	   *e_key = ctx->e_key;
	u4byte		b0[4],
				b1[4],
			   *kp;

	b0[0] = io_swap(in_blk[0]) ^ e_key[0];
	b0[1] = io_swap(in_blk[1]) ^ e_key[1];
	b0[2] = io_swap(in_blk[2]) ^ e_key[2];
	b0[3] = io_swap(in_blk[3]) ^ e_key[3];

	kp = e_key + 4;

	if (k_len > 6)
	{
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	if (k_len > 4)
	{
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_lround(b0, b1, kp);

	out_blk[0] = io_swap(b0[0]);
	out_blk[1] = io_swap(b0[1]);
	out_blk[2] = io_swap(b0[2]);
	out_blk[3] = io_swap(b0[3]);
}