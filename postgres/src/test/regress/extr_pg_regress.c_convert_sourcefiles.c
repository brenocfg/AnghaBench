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
 int /*<<< orphan*/  convert_sourcefiles_in (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  outputdir ; 

__attribute__((used)) static void
convert_sourcefiles(void)
{
	convert_sourcefiles_in("input", outputdir, "sql", "sql");
	convert_sourcefiles_in("output", outputdir, "expected", "out");
}