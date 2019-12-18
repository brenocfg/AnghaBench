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

/* Variables and functions */
 int /*<<< orphan*/  address_direct (char*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* r_str_lchr (char const*,char) ; 
 int /*<<< orphan*/  r_str_ncpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool address_bit(char const* addr_str, ut8* addr_out) {
	char *bitpart = malloc (strlen (addr_str) + 1);
	char *bytepart = malloc (strlen (addr_str) + 1);
	char const *separator = r_str_lchr (addr_str, '.');
	ut8 byte;
	int bit;
	bool ret = false;
	// TODO: check if symbols are resolved properly in all cases:
	// - symbol.2
	// - 0x25.symbol
	// - symbol.symbol
	// - symbol
	if (!separator) {
		goto end;
	}
	r_str_ncpy (bytepart, addr_str, separator - addr_str + 1);
	bytepart[separator - addr_str + 1] = '\0';
	r_str_ncpy (bitpart, separator + 1, strlen (separator));
	if (!address_direct (bytepart, &byte)) {
		goto end;
	}
	if (1 < strlen (bitpart)
		|| bitpart[0] < '0' || '7' < bitpart[0]) {
		ret = false;
		goto end;
	}
	bit = bitpart[0] - '0';
	if (0x20 <= byte && byte < 0x30) {
		*addr_out = (byte - 0x20) * 8 + bit;
		ret = true;
	} else if (0x80 <= byte && !(byte%8)) {
		*addr_out = byte + bit;
		ret = true;
	}
end:
	free (bitpart); bitpart = 0;
	free (bytepart); bytepart = 0;
	return ret;
}