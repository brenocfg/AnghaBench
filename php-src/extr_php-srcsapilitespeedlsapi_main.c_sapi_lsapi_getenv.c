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
 char* LSAPI_GetEnv (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ lsapi_mode ; 

__attribute__((used)) static char *sapi_lsapi_getenv( char * name, size_t name_len )
{
    if ( lsapi_mode ) {
        return LSAPI_GetEnv( name );
    } else {
        return getenv( name );
    }
}