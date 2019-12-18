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
 char*** _NSGetEnviron () ; 
 char** environ ; 
 int /*<<< orphan*/  s_uid ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void unset_lsapi_envs(void)
{
    char **env;
#if defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
    env = *_NSGetEnviron();
#else
    env = environ;
#endif
    while( env != NULL && *env != NULL )
    {
        if (!strncmp(*env, "LSAPI_", 6) || !strncmp( *env, "PHP_LSAPI_", 10 )
            || (!strncmp( *env, "PHPRC=", 6 )&&(!s_uid)))
        {
            char ** del = env;
            do
                *del = del[1];
            while( *del++ );
        }
        else
            ++env;
    }
}