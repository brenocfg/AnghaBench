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
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_file_dump (char*,int /*<<< orphan*/  const*,int,int) ; 
 char* r_file_temp (char*) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void setRarunProfileString(RCore *core, const char *str) {
	char *file = r_file_temp ("rarun2");
	char *s = strdup (str);
	r_config_set (core->config, "dbg.profile", file);
	r_str_replace_char (s, ',', '\n');
	r_file_dump (file, (const ut8*)s, strlen (s), 0);
	r_file_dump (file, (const ut8*)"\n", 1, 1);
	free (file);
}