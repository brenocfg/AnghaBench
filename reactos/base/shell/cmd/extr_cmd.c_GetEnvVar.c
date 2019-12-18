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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  LPCTSTR ;

/* Variables and functions */
 int GetEnvironmentVariable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ *) ; 

LPTSTR
GetEnvVar(LPCTSTR varName)
{
    static LPTSTR ret = NULL;
    UINT size;

    cmd_free(ret);
    ret = NULL;
    size = GetEnvironmentVariable(varName, NULL, 0);
    if (size > 0)
    {
        ret = cmd_alloc(size * sizeof(TCHAR));
        if (ret != NULL)
            GetEnvironmentVariable(varName, ret, size + 1);
    }
    return ret;
}