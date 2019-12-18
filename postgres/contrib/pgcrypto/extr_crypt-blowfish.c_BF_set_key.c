#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* P; } ;
typedef  int BF_word_signed ;
typedef  int BF_word ;
typedef  int* BF_key ;

/* Variables and functions */
 int BF_N ; 
 TYPE_1__ BF_init_state ; 

__attribute__((used)) static void
BF_set_key(const char *key, BF_key expanded, BF_key initial,
		   int sign_extension_bug)
{
	const char *ptr = key;
	int			i,
				j;
	BF_word		tmp;

	for (i = 0; i < BF_N + 2; i++)
	{
		tmp = 0;
		for (j = 0; j < 4; j++)
		{
			tmp <<= 8;
			if (sign_extension_bug)
				tmp |= (BF_word_signed) (signed char) *ptr;
			else
				tmp |= (unsigned char) *ptr;

			if (!*ptr)
				ptr = key;
			else
				ptr++;
		}

		expanded[i] = tmp;
		initial[i] = BF_init_state.P[i] ^ tmp;
	}
}