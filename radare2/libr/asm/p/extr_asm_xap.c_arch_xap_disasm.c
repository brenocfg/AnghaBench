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
typedef  int /*<<< orphan*/  ut64 ;
struct state {unsigned char const* s_buf; scalar_t__ s_ff_quirk; int /*<<< orphan*/ * s_out; int /*<<< orphan*/  s_off; } ;
struct directive {int /*<<< orphan*/  d_inst; int /*<<< orphan*/  d_asm; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct directive*) ; 
 struct state* get_state () ; 
 int i2u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct state*,int /*<<< orphan*/ ,int) ; 
 struct directive* next_inst (struct state*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xap_decode (struct state*,struct directive*) ; 

__attribute__((used)) static int arch_xap_disasm(char *str, const unsigned char *buf, ut64 seek) {
	struct state *s = get_state();
	struct directive *d;
	memset(s, 0, sizeof(*s));
	s->s_buf = buf;
	s->s_off = seek;
	s->s_out = NULL;
	d = next_inst(s);
	if (d != NULL) {
		xap_decode (s, d);
		strcpy (str, d->d_asm);
		free (d);
	} else {
		*str = '\0';
	}
#if 0
	if (s->s_ff_quirk) {
		sprintf(d->d_asm, "DC\t0x%x", i2u16(&d->d_inst));
		s->s_ff_quirk = 0;
	}
#endif
	return 0;
}