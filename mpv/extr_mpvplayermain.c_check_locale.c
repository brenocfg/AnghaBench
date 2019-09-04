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
 int /*<<< orphan*/  LC_NUMERIC ; 
 char* setlocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool check_locale(void)
{
    char *name = setlocale(LC_NUMERIC, NULL);
    return !name || strcmp(name, "C") == 0 || strcmp(name, "C.UTF-8") == 0;
}