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
typedef  int ut8 ;
typedef  int ut32 ;

/* Variables and functions */
 int* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int strlen (char const*) ; 

ut32 *utf8toutf32 (const ut8 *input) {
	if (!input) {
		eprintf ("ERROR input is null\n");
		return NULL;
	}

	int i = 0;
	int j = 0;
	int val = 0;
	int len = strlen ((const char *) input);
	ut32 *result = calloc (strlen ((const char *) input) + 1, 4);

	if (!result) {
		eprintf ("ERROR: out of memory\n");
		return NULL;
	}

	while (i < len) {
		if (input[i] >> 7 == 0) {
			val = input[i];
			i += 1;
		} else if (input[i] >> 5 == 0x6) {
			val = (((input[i] & 0x1f) << 6) & 0xfc0) |
			(input[i + 1] & 0x3f);
			i += 2;
		} else if (input[i] >> 4 == 0xe) {
			val = (((input[i] & 0xf) << 12) & 0xf000) |
			(((input[i + 1] & 0x3f) << 6) & 0xffc0) |
			(input[i + 2] & 0x3f);
			i += 3;
		} else if (input[i] >> 3 == 0x1e) {
			val = (((input[i] & 0xf) << 18) & 0x1c0000) |
			(((input[i + 1] & 0x3f) << 12) & 0x1ff000) |
			(((input[i + 2] & 0x3f) << 6) & 0x1fffc0) |
			(input[i + 3] & 0x3f);
			i += 4;
		} else {
			eprintf ("ERROR in toutf32. Seems like input is invalid.\n");
			free (result);
			return NULL;
		}
		result[j] = val;
		j++;
	}

	return result;
}