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
typedef  char const ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
#define  R_SIGN_ANAL 129 
#define  R_SIGN_BYTES 128 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,int) ; 
 int r_hex_str2bin (char*,char const*) ; 
 int r_hex_str2binmask (char const*,char const*,char const*) ; 
 int r_sign_add_anal (int /*<<< orphan*/ ,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 int r_sign_add_bytes (int /*<<< orphan*/ ,char const*,int,char const*,char const*) ; 
 char* r_str_word_get0 (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool addBytesZign(RCore *core, const char *name, int type, const char *args0, int nargs) {
	const char *hexbytes = NULL;
	ut8 *mask = NULL, *bytes = NULL, *sep = NULL;
	int size = 0, blen = 0;
	bool retval = true;

	if (nargs != 1) {
		eprintf ("error: invalid syntax\n");
		retval = false;
		goto out;
	}

	hexbytes = r_str_word_get0 (args0, 0);
	if ((sep = (ut8*) strchr (hexbytes, ':'))) {
		blen = sep - (ut8*) hexbytes;
		if (!blen || (blen & 1) || strlen ((char*) ++sep) != blen) {
			eprintf ("error: cannot parse hexpairs\n");
			retval = false;
			goto out;
		}
		bytes = calloc (1, blen + 1);
		mask = calloc (1, blen + 1);
		memcpy (bytes, hexbytes, blen);
		memcpy (mask, sep, blen);
		size = r_hex_str2bin ((char*) bytes, bytes);
		if (size != blen / 2 || r_hex_str2bin ((char*) mask, mask) != size) {
			eprintf ("error: cannot parse hexpairs\n");
			retval = false;
			goto out;
		}
	} else {
		blen = strlen (hexbytes) + 4;
		bytes = malloc (blen);
		mask = malloc (blen);

		size = r_hex_str2binmask (hexbytes, bytes, mask);
		if (size <= 0) {
			eprintf ("error: cannot parse hexpairs\n");
			retval = false;
			goto out;
		}
	}

	switch (type) {
	case R_SIGN_BYTES:
		retval = r_sign_add_bytes (core->anal, name, size, bytes, mask);
		break;
	case R_SIGN_ANAL:
		retval = r_sign_add_anal (core->anal, name, size, bytes, 0);
		break;
	}

out:
	free (bytes);
	free (mask);

	return retval;
}