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
struct TYPE_3__ {int len; int prefix; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 TYPE_1__* _s ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ r_file_slurp (char const*,int*) ; 
 int r_hex_str2bin (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ r_stdin_slurp (int*) ; 
 TYPE_1__ s ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static void do_hash_seed(const char *seed) {
	const char *sptr = seed;
	if (!seed) {
		_s = NULL;
		return;
	}
	_s = &s;
	if (!strcmp (seed, "-")) {
		s.buf = (ut8 *)r_stdin_slurp (&s.len);
		return;
	}
	if (seed[0] == '@') {
		s.buf = (ut8 *)r_file_slurp (seed + 1, &s.len);
		return;
	}
	s.buf = (ut8 *) malloc (strlen (seed) + 128);
	if (!s.buf) {
		_s = NULL;
		return;
	}
	if (*seed == '^') {
		s.prefix = 1;
		sptr++;
	} else {
		s.prefix = 0;
	}
	if (!strncmp (sptr, "s:", 2)) {
		strcpy ((char *) s.buf, sptr + 2);
		s.len = strlen (sptr + 2);
	} else {
		s.len = r_hex_str2bin (sptr, s.buf);
		if (s.len < 1) {
			strcpy ((char *) s.buf, sptr);
			s.len = strlen (sptr);
			eprintf ("Warning: This is not an hexpair, assuming a string, prefix it with 's:' to skip this message.");
		}
	}
}