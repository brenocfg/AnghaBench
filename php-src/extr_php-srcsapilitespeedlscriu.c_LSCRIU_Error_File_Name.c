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
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static char *LSCRIU_Error_File_Name(char *pchFile, int max_len)
{
    const char *pchDefaultSocketPath = "/tmp/";
    const char *pchDefaultLogFileName = "lsws_error.log";
    snprintf(pchFile, max_len, "%s%s", pchDefaultSocketPath,
             pchDefaultLogFileName);
    return pchFile;
}