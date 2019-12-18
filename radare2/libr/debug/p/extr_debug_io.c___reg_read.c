#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char ut8 ;
struct TYPE_4__ {char* (* system ) (int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  io; } ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIN (int,int) ; 
 char* calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 char* r_cons_get_buffer () ; 
 int /*<<< orphan*/  r_cons_reset () ; 
 int r_hex_str2bin (char*,char*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int __reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
	char *dr8 = dbg->iob.system (dbg->iob.io, "dr8");
	if (!dr8) {
		const char *fb = r_cons_get_buffer ();
		if (!fb || !*fb) {
			eprintf ("debug.io: Failed to get dr8 from io\n");
			return -1;
		}
		dr8 = strdup (fb);
		r_cons_reset ();
	}
	ut8 *bregs = calloc (1, strlen (dr8));
	if (!bregs) {
		free (dr8);
		return -1;
	}
	r_str_trim ((char *)bregs);
	int sz = r_hex_str2bin (dr8, bregs);
	if (sz > 0) {
		memcpy (buf, bregs, R_MIN (size, sz));
		free (bregs);
		free (dr8);
		return size;
	} else {
		// eprintf ("SIZE %d (%s)\n", sz, regs);
	}
	free (bregs);
	free (dr8);
	return -1;
}