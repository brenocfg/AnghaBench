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
typedef  scalar_t__ uint8 ;
typedef  int uint64 ;
struct TYPE_3__ {int* state; scalar_t__ buffer; } ;
typedef  TYPE_1__ pg_sha512_ctx ;

/* Variables and functions */
 int Ch (int,int,int) ; 
 int* K512 ; 
 int Maj (int,int,int) ; 
 int Sigma0_512 (int) ; 
 int Sigma1_512 (int) ; 
 int sigma0_512 (int) ; 
 int sigma1_512 (int) ; 

__attribute__((used)) static void
SHA512_Transform(pg_sha512_ctx *context, const uint8 *data)
{
	uint64		a,
				b,
				c,
				d,
				e,
				f,
				g,
				h,
				s0,
				s1;
	uint64		T1,
				T2,
			   *W512 = (uint64 *) context->buffer;
	int			j;

	/* Initialize registers with the prev. intermediate value */
	a = context->state[0];
	b = context->state[1];
	c = context->state[2];
	d = context->state[3];
	e = context->state[4];
	f = context->state[5];
	g = context->state[6];
	h = context->state[7];

	j = 0;
	do
	{
		W512[j] = (uint64) data[7] | ((uint64) data[6] << 8) |
			((uint64) data[5] << 16) | ((uint64) data[4] << 24) |
			((uint64) data[3] << 32) | ((uint64) data[2] << 40) |
			((uint64) data[1] << 48) | ((uint64) data[0] << 56);
		data += 8;
		/* Apply the SHA-512 compression function to update a..h */
		T1 = h + Sigma1_512(e) + Ch(e, f, g) + K512[j] + W512[j];
		T2 = Sigma0_512(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	} while (j < 16);

	do
	{
		/* Part of the message block expansion: */
		s0 = W512[(j + 1) & 0x0f];
		s0 = sigma0_512(s0);
		s1 = W512[(j + 14) & 0x0f];
		s1 = sigma1_512(s1);

		/* Apply the SHA-512 compression function to update a..h */
		T1 = h + Sigma1_512(e) + Ch(e, f, g) + K512[j] +
			(W512[j & 0x0f] += s1 + W512[(j + 9) & 0x0f] + s0);
		T2 = Sigma0_512(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

		j++;
	} while (j < 80);

	/* Compute the current intermediate hash value */
	context->state[0] += a;
	context->state[1] += b;
	context->state[2] += c;
	context->state[3] += d;
	context->state[4] += e;
	context->state[5] += f;
	context->state[6] += g;
	context->state[7] += h;

	/* Clean up */
	a = b = c = d = e = f = g = h = T1 = T2 = 0;
}