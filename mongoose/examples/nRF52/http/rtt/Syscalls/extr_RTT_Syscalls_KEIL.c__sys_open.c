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
typedef  int /*<<< orphan*/  FILEHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR ; 
 int /*<<< orphan*/  STDOUT ; 
 int /*<<< orphan*/  __stderr_name ; 
 int /*<<< orphan*/  __stdout_name ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

FILEHANDLE _sys_open(const char * sName, int OpenMode) {
  // Register standard Input Output devices.
  if (strcmp(sName, __stdout_name) == 0) {
    return (STDOUT);
  } else if (strcmp(sName, __stderr_name) == 0) {
    return (STDERR);
  } else
  return (0);  // Not implemented
}