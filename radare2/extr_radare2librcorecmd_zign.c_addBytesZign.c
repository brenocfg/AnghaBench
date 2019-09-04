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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
#define  R_SIGN_ANAL 129 
#define  R_SIGN_BYTES 128 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int r_hex_str2binmask (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int r_sign_add_anal (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int r_sign_add_bytes (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* r_str_word_get0 (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool addBytesZign(RCore *core, const char *name, int type, const char *args0, int nargs) {
	const char *hexbytes = NULL;
	ut8 *mask = NULL, *bytes = NULL;
	int size = 0, blen = 0;
	bool retval = true;

	if (nargs != 1) {
		eprintf ("error: invalid syntax\n");
		retval = false;
		goto out;
	}

	hexbytes = r_str_word_get0 (args0, 0);
	blen = strlen (hexbytes) + 4;
	bytes = malloc (blen);
	mask = malloc (blen);

	size = r_hex_str2binmask (hexbytes, bytes, mask);
	if (size <= 0) {
		eprintf ("error: cannot parse hexpairs\n");
		retval = false;
		goto out;
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