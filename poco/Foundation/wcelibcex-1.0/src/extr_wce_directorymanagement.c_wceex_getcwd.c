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
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  Cwd ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ InitCwd () ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 

char* wceex_getcwd( char *buffer, int maxlen )
{
    if( !buffer && (buffer = (char*)malloc(maxlen)) == NULL )
    {
        errno = ENOMEM;
        return NULL;
    }
    if( InitCwd() )
        return NULL;    
	if( !WideCharToMultiByte( CP_ACP, 0, Cwd, -1, buffer, maxlen, NULL, NULL ) )
    {
        errno = GetLastError();
        return NULL;
    }
    return buffer;
}