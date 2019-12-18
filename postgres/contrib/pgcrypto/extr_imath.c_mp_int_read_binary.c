#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_result ;
typedef  TYPE_1__* mp_int ;
typedef  unsigned char mp_digit ;
struct TYPE_8__ {scalar_t__ sign; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 unsigned char* MP_DIGITS (TYPE_1__*) ; 
 int MP_DIGIT_BIT ; 
 int /*<<< orphan*/  MP_MEMORY ; 
 scalar_t__ MP_NEG ; 
 int /*<<< orphan*/  MP_OK ; 
 scalar_t__ MP_SIGN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_int_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  s_2comp (unsigned char*,int) ; 
 int /*<<< orphan*/  s_pad (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_qmul (TYPE_1__*,int) ; 

mp_result
mp_int_read_binary(mp_int z, unsigned char *buf, int len)
{
	assert(z != NULL && buf != NULL && len > 0);

	/* Figure out how many digits are needed to represent this value */
	mp_size		need = ((len * CHAR_BIT) + (MP_DIGIT_BIT - 1)) / MP_DIGIT_BIT;

	if (!s_pad(z, need))
		return MP_MEMORY;

	mp_int_zero(z);

	/*
	 * If the high-order bit is set, take the 2's complement before reading
	 * the value (it will be restored afterward)
	 */
	if (buf[0] >> (CHAR_BIT - 1))
	{
		z->sign = MP_NEG;
		s_2comp(buf, len);
	}

	mp_digit   *dz = MP_DIGITS(z);
	unsigned char *tmp = buf;

	for (int i = len; i > 0; --i, ++tmp)
	{
		s_qmul(z, (mp_size) CHAR_BIT);
		*dz |= *tmp;
	}

	/* Restore 2's complement if we took it before */
	if (MP_SIGN(z) == MP_NEG)
		s_2comp(buf, len);

	return MP_OK;
}