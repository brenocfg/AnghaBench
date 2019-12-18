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
typedef  scalar_t__ TCHAR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectory (int,scalar_t__*) ; 
 scalar_t__ _T (char) ; 
 int /*<<< orphan*/ * _tgetdcwd (int,scalar_t__*,int) ; 

INT GetRootPath(TCHAR *InPath,TCHAR *OutPath,INT size)
{
    if (InPath[0] && InPath[1] == _T(':'))
    {
        INT t=0;

        if ((InPath[0] >= _T('0')) && (InPath[0] <= _T('9')))
        {
            t = (InPath[0] - _T('0')) +28;
        }

        if ((InPath[0] >= _T('a')) && (InPath[0] <= _T('z')))
        {
            t = (InPath[0] - _T('a')) +1;
            InPath[0] = t + _T('A') - 1;
        }

        if ((InPath[0] >= _T('A')) && (InPath[0] <= _T('Z')))
        {
            t = (InPath[0] - _T('A')) +1;
        }

        return _tgetdcwd(t,OutPath,size) == NULL;
    }

    /* Get current directory */
    return !GetCurrentDirectory(size,OutPath);
}