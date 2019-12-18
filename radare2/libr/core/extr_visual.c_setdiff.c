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
typedef  int /*<<< orphan*/  to ;
typedef  int /*<<< orphan*/  from ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  prompt_read (char*,char*,int) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void setdiff(RCore *core) {
	char from[64], to[64];
	prompt_read ("diff from: ", from, sizeof (from));
	r_config_set (core->config, "diff.from", from);
	prompt_read ("diff to: ", to, sizeof (to));
	r_config_set (core->config, "diff.to", to);
}