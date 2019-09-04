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
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OutputDebugString (char*) ; 
 int /*<<< orphan*/  OutputDebugStringA (char*) ; 
 char _T (char) ; 
 int /*<<< orphan*/  _pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _popen (char*,char*) ; 
 int /*<<< orphan*/  _putts (char*) ; 
 int _tcslen (char*) ; 
 int /*<<< orphan*/  _tcsncpy (char*,char*,size_t) ; 
 scalar_t__ _tcsstr (char*,char*) ; 
 int /*<<< orphan*/ * _tpopen (char*,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int _tmain(int argc, TCHAR ** argv)
{
    TCHAR * buf;
    size_t bufsize;
    int i;
    size_t offset;

    bufsize = 0;
    for(i = 1; i < argc; i++)
    {
        bufsize += _tcslen(argv[i]) + 1;
    }

    if (!bufsize)
    {
        return -1;
    }

    if (_tcsstr(argv[1], "--winetest") && (argc == 3))
    {
        char   psBuffer[128];
        char   psBuffer2[128];
        char   *nlptr2;
        char   cmd[255];
        char   test[300];
        FILE   *pPipe;
        FILE   *pPipe2;

        /* get available tests */
        strcpy(cmd, argv[2]);
        strcat(cmd, " --list");
        pPipe = _tpopen(cmd, "r");
        if (pPipe != NULL)
        {
            while(fgets(psBuffer, 128, pPipe))
            {
                if (psBuffer[0] == ' ')
                {
                    strcpy(cmd, argv[2]);
                    strcat(cmd, " ");
                    strcat(cmd, psBuffer+4);
                    /* run the current test */
                    strcpy(test, "\n\nRunning ");
                    strcat(test, cmd);
                    OutputDebugStringA(test);
                    pPipe2 = _popen(cmd, "r");
                    if (pPipe2 != NULL)
                    {
                        while(fgets(psBuffer2, 128, pPipe2))
                        {
                            nlptr2 = strchr(psBuffer2, '\n');
                            if (nlptr2)
                                *nlptr2 = '\0';
                            puts(psBuffer2);
                            if (nlptr2)
                                *nlptr2 = '\n';
                            OutputDebugStringA(psBuffer2);
                        }
                        _pclose(pPipe2);
                    }
                }
            }
            _pclose(pPipe);
        }
    }
    else if (_tcsstr(argv[1], "--process") && (argc == 3))
    {
        char   psBuffer[128];
        FILE   *pPipe;

        pPipe = _tpopen(argv[2], "r");
        if (pPipe != NULL)
        {
            while(fgets(psBuffer, 128, pPipe))
            {
                puts(psBuffer);
                OutputDebugStringA(psBuffer);
            }
            _pclose(pPipe);
        }
    }
    else
    {
        buf = HeapAlloc(GetProcessHeap(), 0, (bufsize+1) * sizeof(TCHAR));
        if (!buf)
        {
            return -1;
        }

        offset = 0;
        for(i = 1; i < argc; i++)
        {
            size_t length = _tcslen(argv[i]);
            _tcsncpy(&buf[offset], argv[i], length);
            offset += length;
            if (i + 1 < argc)
            {
                buf[offset] = _T(' ');
            }
            else
            {
                buf[offset] = _T('\n');
                buf[offset+1] = _T('\0');
            }
            offset++;
        }
        _putts(buf);
        OutputDebugString(buf);
        HeapFree(GetProcessHeap(), 0, buf);
    }
    return 0;
}