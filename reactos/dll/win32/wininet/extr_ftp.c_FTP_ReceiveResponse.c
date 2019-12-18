#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  sndSocket; } ;
typedef  TYPE_1__ ftp_session_t ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FTP_GetNextLine (int /*<<< orphan*/ ,int*) ; 
 char* INTERNET_GetResponseBuffer () ; 
 int /*<<< orphan*/  INTERNET_STATUS_RECEIVING_RESPONSE ; 
 int /*<<< orphan*/  INTERNET_STATUS_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

INT FTP_ReceiveResponse(ftp_session_t *lpwfs, DWORD_PTR dwContext)
{
    LPSTR lpszResponse = INTERNET_GetResponseBuffer();
    DWORD nRecv;
    INT rc = 0;
    char firstprefix[5];
    BOOL multiline = FALSE;

    TRACE("socket(%d)\n", lpwfs->sndSocket);

    INTERNET_SendCallback(&lpwfs->hdr, dwContext, INTERNET_STATUS_RECEIVING_RESPONSE, NULL, 0);

    while(1)
    {
	if (!FTP_GetNextLine(lpwfs->sndSocket, &nRecv))
	    goto lerror;

        if (nRecv >= 3)
	{
	    if(!multiline)
	    {
	        if(lpszResponse[3] != '-')
		    break;
		else
		{  /* Start of multiline response.  Loop until we get "nnn " */
		    multiline = TRUE;
		    memcpy(firstprefix, lpszResponse, 3);
		    firstprefix[3] = ' ';
		    firstprefix[4] = '\0';
		}
	    }
	    else
	    {
	        if(!memcmp(firstprefix, lpszResponse, 4))
		    break;
	    }
	}
    }

    if (nRecv >= 3)
    {
        rc = atoi(lpszResponse);

        INTERNET_SendCallback(&lpwfs->hdr, dwContext, INTERNET_STATUS_RESPONSE_RECEIVED,
		    &nRecv, sizeof(DWORD));
    }

lerror:
    TRACE("return %d\n", rc);
    return rc;
}