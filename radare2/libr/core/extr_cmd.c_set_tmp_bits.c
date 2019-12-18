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
struct TYPE_3__ {int fixedbits; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_tmp_bits(RCore *core, int bits, char **tmpbits) {
	if (!tmpbits) {
		eprintf ("tmpbits should be set\n");
	}
	*tmpbits = strdup (r_config_get (core->config, "asm.bits"));
	r_config_set_i (core->config, "asm.bits", bits);
	core->fixedbits = true;
	return true;
}