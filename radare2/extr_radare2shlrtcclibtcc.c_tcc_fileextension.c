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
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 char* tcc_basename (char const*) ; 

char *tcc_fileextension(const char *name)
{
	char *b = tcc_basename (name);
	char *e = strrchr (b, '.');
	return e? e: strchr (b, 0);
}