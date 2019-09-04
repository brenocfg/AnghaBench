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
#define  R_EGG_OS_FREEBSD 131 
#define  R_EGG_OS_OSX 130 
#define  R_SYS_ARCH_ARM 129 
#define  R_SYS_ARCH_X86 128 
 int /*<<< orphan*/ * armle_osx_reverse ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int /*<<< orphan*/  r_buf_set_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_write_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* r_egg_option_get (TYPE_1__*,char*) ; 
 char const* shell ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char const* suid ; 
 int /*<<< orphan*/ * x86_freebsd_reverse ; 

__attribute__((used)) static RBuffer *build (REgg *egg) {
	RBuffer *buf = r_buf_new ();
	const ut8 *sc = NULL;
	int cd = 0;
	char *port = r_egg_option_get (egg, "port");
	//TODO: char *udp = r_egg_option_get (egg, "udp");
	switch (egg->os) {
	case R_EGG_OS_OSX:
	case R_EGG_OS_DARWIN:
		switch (egg->arch) {
		case R_SYS_ARCH_ARM:
			sc = armle_osx_reverse;
			cd = 7+36;
			break;
		}
		break;
	case R_EGG_OS_FREEBSD:
		switch (egg->arch) {
		case R_SYS_ARCH_X86:
			switch (egg->bits) {
			case 32: sc = x86_freebsd_reverse; break;
			default: eprintf ("Unsupportted\n");
			}
			break;
		}
		break;
	default:
		eprintf ("unsupported os %x\n", egg->os);
		break;
	}
	if (sc) {
		r_buf_set_bytes (buf, sc, strlen ((const char *)sc));
		if (shell && *shell) {
			if (cd) r_buf_write_at (buf, cd, (const ut8*)shell, strlen (shell)+1);
			else eprintf ("Cannot set shell\n");
		}
	}
	free (suid);
	free (shell);
	return buf;
}