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
 int /*<<< orphan*/  H_COOKIE ; 
 char* LSAPI_GetHeader (int /*<<< orphan*/ ) ; 
 scalar_t__ lsapi_mode ; 

__attribute__((used)) static char *sapi_lsapi_read_cookies(void)
{
    if ( lsapi_mode ) {
        return LSAPI_GetHeader( H_COOKIE );
    } else {
        return NULL;
    }
}