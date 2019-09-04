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
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 char* strdupz (char*) ; 

__attribute__((used)) static inline char *health_source_file(size_t line, const char *file) {
    char buffer[FILENAME_MAX + 1];
    snprintfz(buffer, FILENAME_MAX, "%zu@%s", line, file);
    return strdupz(buffer);
}