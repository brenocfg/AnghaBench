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
typedef  int /*<<< orphan*/  REgg ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_egg_assemble (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_egg_compile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_egg_encode (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_egg_get_bin (int /*<<< orphan*/ *) ; 
 char* r_egg_option_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_egg_option_set (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  r_egg_padding (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_egg_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_egg_shellcode (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  showBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmd_egg_compile(REgg *egg) {
	RBuffer *b;
	int ret = false;
	char *p = r_egg_option_get (egg, "egg.shellcode");
	if (p && *p) {
		if (!r_egg_shellcode (egg, p)) {
			eprintf ("Unknown shellcode '%s'\n", p);
			free (p);
			return false;
		}
		free (p);
	} else {
		eprintf ("Setup a shellcode before (gi command)\n");
		free (p);
		return false;
	}

	r_egg_compile (egg);
	if (!r_egg_assemble (egg)) {
		eprintf ("r_egg_assemble: invalid assembly\n");
		return false;
	}
	p = r_egg_option_get (egg, "egg.padding");
	if (p && *p) {
		r_egg_padding (egg, p);
		free (p);
	}
	p = r_egg_option_get (egg, "egg.encoder");
	if (p && *p) {
		r_egg_encode (egg, p);
		free (p);
	}
	if ((b = r_egg_get_bin (egg))) {
		showBuffer (b);
		ret = true;
	}
	// we do not own this buffer!!
	// r_buf_free (b);
	r_egg_option_set (egg, "egg.shellcode", "");
	r_egg_option_set (egg, "egg.padding", "");
	r_egg_option_set (egg, "egg.encoder", "");
	r_egg_option_set (egg, "key", "");

	r_egg_reset (egg);
	return ret;
}