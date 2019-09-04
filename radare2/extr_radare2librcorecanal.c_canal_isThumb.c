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
struct TYPE_5__ {TYPE_1__* anal; int /*<<< orphan*/  config; } ;
struct TYPE_4__ {int bits; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static inline bool canal_isThumb(RCore *core) {
	const char *asmarch = r_config_get (core->config, "asm.arch");
	return (!strcmp (asmarch, "arm") && core->anal->bits == 16);
}