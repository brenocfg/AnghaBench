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
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CMDLINE_LENGTH ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__ _fgetts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmd_alloc (int) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmd_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LPTSTR ReadFileContents(FILE *InputFile, TCHAR *Buffer)
{
    SIZE_T Len = 0;
    SIZE_T AllocLen = 1000;

    LPTSTR Contents = cmd_alloc(AllocLen * sizeof(TCHAR));
    if (!Contents)
    {
        WARN("Cannot allocate memory for Contents!\n");
        return NULL;
    }

    while (_fgetts(Buffer, CMDLINE_LENGTH, InputFile))
    {
        ULONG_PTR CharsRead = _tcslen(Buffer);
        while (Len + CharsRead >= AllocLen)
        {
            LPTSTR OldContents = Contents;
            Contents = cmd_realloc(Contents, (AllocLen *= 2) * sizeof(TCHAR));
            if (!Contents)
            {
                WARN("Cannot reallocate memory for Contents!\n");
                cmd_free(OldContents);
                return NULL;
            }
        }
        _tcscpy(&Contents[Len], Buffer);
        Len += CharsRead;
    }

    Contents[Len] = _T('\0');
    return Contents;
}