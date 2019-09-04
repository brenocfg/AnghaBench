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
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  in_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 

RD_BOOL
ber_in_header(STREAM s, int *tagval, int *decoded_len)
{
	in_uint8(s, *tagval);
	in_uint8(s, *decoded_len);

	if (*decoded_len < 0x80)
		return True;
	else if (*decoded_len == 0x81)
	{
		in_uint8(s, *decoded_len);
		return True;
	}
	else if (*decoded_len == 0x82)
	{
		in_uint16_be(s, *decoded_len);
		return True;
	}

	return False;
}