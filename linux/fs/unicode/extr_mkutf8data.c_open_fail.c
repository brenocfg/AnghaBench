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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int,char const*,char*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void open_fail(const char *name, int error)
{
	printf("Error %d opening %s: %s\n", error, name, strerror(error));
	exit(1);
}