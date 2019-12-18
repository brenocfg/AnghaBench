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
typedef  size_t mp_size ;

/* Variables and functions */
 int MP_DIGIT_BIT ; 
 double* s_log2 ; 

__attribute__((used)) static mp_size
s_inlen(int len, mp_size r)
{
	double		raw = (double) len / s_log2[r];
	mp_size		bits = (mp_size) (raw + 0.5);

	return (mp_size) ((bits + (MP_DIGIT_BIT - 1)) / MP_DIGIT_BIT) + 1;
}