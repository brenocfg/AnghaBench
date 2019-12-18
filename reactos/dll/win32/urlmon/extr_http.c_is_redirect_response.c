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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  HTTP_STATUS_MOVED 131 
#define  HTTP_STATUS_REDIRECT 130 
#define  HTTP_STATUS_REDIRECT_KEEP_VERB 129 
#define  HTTP_STATUS_REDIRECT_METHOD 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_redirect_response(DWORD status_code)
{
    switch(status_code) {
    case HTTP_STATUS_REDIRECT:
    case HTTP_STATUS_MOVED:
    case HTTP_STATUS_REDIRECT_KEEP_VERB:
    case HTTP_STATUS_REDIRECT_METHOD:
        return TRUE;
    }
    return FALSE;
}