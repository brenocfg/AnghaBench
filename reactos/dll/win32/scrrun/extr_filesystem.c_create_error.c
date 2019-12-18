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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_E_FILEALREADYEXISTS ; 
 int /*<<< orphan*/  CTL_E_FILENOTFOUND ; 
 int /*<<< orphan*/  CTL_E_PATHNOTFOUND ; 
 int /*<<< orphan*/  CTL_E_PERMISSIONDENIED ; 
#define  ERROR_ACCESS_DENIED 132 
#define  ERROR_ALREADY_EXISTS 131 
#define  ERROR_FILE_EXISTS 130 
#define  ERROR_FILE_NOT_FOUND 129 
#define  ERROR_PATH_NOT_FOUND 128 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static inline HRESULT create_error(DWORD err)
{
    switch(err) {
    case ERROR_FILE_NOT_FOUND: return CTL_E_FILENOTFOUND;
    case ERROR_PATH_NOT_FOUND: return CTL_E_PATHNOTFOUND;
    case ERROR_ACCESS_DENIED: return CTL_E_PERMISSIONDENIED;
    case ERROR_FILE_EXISTS: return CTL_E_FILEALREADYEXISTS;
    case ERROR_ALREADY_EXISTS: return CTL_E_FILEALREADYEXISTS;
    default:
        FIXME("Unsupported error code: %d\n", err);
        return E_FAIL;
    }
}