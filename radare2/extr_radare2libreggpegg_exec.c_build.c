#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int os; int /*<<< orphan*/  bits; int /*<<< orphan*/  arch; } ;
typedef  TYPE_1__ REgg ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
#define  R_EGG_OS_DARWIN 132 
#define  R_EGG_OS_LINUX 131 
#define  R_EGG_OS_OSX 130 
#define  R_SYS_ARCH_ARM 129 
#define  R_SYS_ARCH_X86 128 
 int /*<<< orphan*/ * arm_linux_binsh ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int /*<<< orphan*/  r_buf_set_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  r_buf_write_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,scalar_t__) ; 
 char* r_egg_option_get (TYPE_1__*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * thumb_linux_binsh ; 
 int /*<<< orphan*/ * x86_64_linux_binsh ; 
 int /*<<< orphan*/ * x86_linux_binsh ; 
 int /*<<< orphan*/ * x86_osx_binsh ; 
 int /*<<< orphan*/ * x86_osx_suid_binsh ; 

__attribute__((used)) static RBuffer *build (REgg *egg) {
	RBuffer *buf = r_buf_new ();
	const ut8 *sc = NULL;
	int cd = 0;
	char *shell = r_egg_option_get (egg, "cmd");
	char *suid = r_egg_option_get (egg, "suid");
	// TODO: last char must not be \x00 .. or what? :D
	if (suid && *suid=='f') { // false
		free (suid);
		suid = NULL;
	}
	switch (egg->os) {
	case R_EGG_OS_OSX:
	case R_EGG_OS_DARWIN:
		switch (egg->arch) {
		case R_SYS_ARCH_X86:
			if (suid) {
				sc = x86_osx_suid_binsh;
				cd = 7+36;
			} else {
				sc = x86_osx_binsh;
				cd = 36;
			}
		case R_SYS_ARCH_ARM:
			// TODO
			break;
		}
		break;
	case R_EGG_OS_LINUX:
		if (suid) {
			eprintf ("no suid for this platform\n");
		}
		suid = 0;
		switch (egg->arch) {
		case R_SYS_ARCH_X86:
			switch (egg->bits) {
			case 32:
				sc = x86_linux_binsh;
				break;
			case 64:
				sc = x86_64_linux_binsh;
				break;
			default:
				eprintf ("Unsupported arch %d bits\n", egg->bits);
			}
			break;
		case R_SYS_ARCH_ARM:
			switch (egg->bits) {
			case 16:
				sc = thumb_linux_binsh;
				break;
			case 32:
				sc = arm_linux_binsh;
				break;
			default:
				eprintf ("Unsupported arch %d bits\n", egg->bits);
			}
			break;
		}
		break;
	default:
		eprintf ("Unsupported os %x\n", egg->os);
		break;
	}

	if (sc) {
		r_buf_set_bytes (buf, sc, strlen ((const char *)sc));
		if (shell && *shell) {
			if (cd) {
				r_buf_write_at (buf, cd, (const ut8 *)shell, strlen (shell) + 1);
			} else {
				eprintf ("Cannot set shell\n");
			}
		}
	}
	free (suid);
	free (shell);
	return buf;
}