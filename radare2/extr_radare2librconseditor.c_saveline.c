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

/* Variables and functions */
 int /*<<< orphan*/  _n ; 
 int /*<<< orphan*/  bytes ; 
 int /*<<< orphan*/  free (char*) ; 
 char* lines ; 
 char* r_str_word_get0set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saveline(int n, const char *str) {
	char *out;
	if (!str) {
		return;
	}
	out = r_str_word_get0set (lines, bytes, _n, str, &bytes);
	free (lines);
	lines = out;
}