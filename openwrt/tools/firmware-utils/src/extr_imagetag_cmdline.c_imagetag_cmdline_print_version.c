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
 char* IMAGETAG_CMDLINE_PACKAGE ; 
 char* IMAGETAG_CMDLINE_PACKAGE_NAME ; 
 char* IMAGETAG_CMDLINE_VERSION ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
imagetag_cmdline_print_version (void)
{
  printf ("%s %s\n",
     (strlen(IMAGETAG_CMDLINE_PACKAGE_NAME) ? IMAGETAG_CMDLINE_PACKAGE_NAME : IMAGETAG_CMDLINE_PACKAGE),
     IMAGETAG_CMDLINE_VERSION);
}