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
typedef  int /*<<< orphan*/  UINT ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSTALL_FAILURE ; 
 int /*<<< orphan*/  ERROR_INSTALL_SUSPEND ; 
 int /*<<< orphan*/  ERROR_INSTALL_USEREXIT ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
#define  IDABORT 132 
#define  IDCANCEL 131 
#define  IDIGNORE 130 
#define  IDOK 129 
#define  IDRETRY 128 

__attribute__((used)) static UINT map_return_value(LONG val)
{
    switch (val)
    {
    case 0:
    case IDOK:
    case IDIGNORE:  return ERROR_SUCCESS;
    case IDCANCEL:  return ERROR_INSTALL_USEREXIT;
    case IDRETRY:   return ERROR_INSTALL_SUSPEND;
    case IDABORT:
    default:        return ERROR_INSTALL_FAILURE;
    }
}