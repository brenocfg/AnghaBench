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
typedef  int /*<<< orphan*/  RLang ;

/* Variables and functions */
 int lang_vala_file (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int vala_run_file(RLang *lang, const char *file) {
	return lang_vala_file(lang, file, false);
}