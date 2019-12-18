#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_9__ {TYPE_2__ S_un; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_3__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_10__ {int pasvSocket; struct sockaddr_in socketAddress; TYPE_1__ hdr; int /*<<< orphan*/  sndSocket; } ;
typedef  TYPE_4__ ftp_session_t ;
typedef  int /*<<< orphan*/  dataSocketAddress ;
typedef  char* LPSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_CMD_PASV ; 
 int FTP_ReceiveResponse (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_SetResponseError (int) ; 
 char* INTERNET_GetResponseBuffer () ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static BOOL FTP_DoPassive(ftp_session_t *lpwfs)
{
    INT nResCode;
    BOOL bSuccess = FALSE;

    TRACE("\n");
    if (!FTP_SendCommand(lpwfs->sndSocket, FTP_CMD_PASV, NULL, 0, 0, 0))
        goto lend;

    nResCode = FTP_ReceiveResponse(lpwfs, lpwfs->hdr.dwContext);
    if (nResCode)
    {
        if (nResCode == 227)
	{
	    LPSTR lpszResponseBuffer = INTERNET_GetResponseBuffer();
	    LPSTR p;
	    int f[6];
	    int i;
	    char *pAddr, *pPort;
	    INT nsocket = -1;
	    struct sockaddr_in dataSocketAddress;

	    p = lpszResponseBuffer+4; /* skip status code */
	    while (*p != '\0' && (*p < '0' || *p > '9')) p++;

	    if (*p == '\0')
	    {
		ERR("no address found in response, aborting\n");
		goto lend;
	    }

	    if (sscanf(p, "%d,%d,%d,%d,%d,%d",  &f[0], &f[1], &f[2], &f[3],
				    		&f[4], &f[5]) != 6)
	    {
		ERR("unknown response address format '%s', aborting\n", p);
		goto lend;
	    }
	    for (i=0; i < 6; i++)
		f[i] = f[i] & 0xff;

	    dataSocketAddress = lpwfs->socketAddress;
	    pAddr = (char *)&(dataSocketAddress.sin_addr.S_un.S_addr);
	    pPort = (char *)&(dataSocketAddress.sin_port);
            pAddr[0] = f[0];
            pAddr[1] = f[1];
            pAddr[2] = f[2];
            pAddr[3] = f[3];
	    pPort[0] = f[4];
	    pPort[1] = f[5];

            nsocket = socket(AF_INET,SOCK_STREAM,0);
            if (nsocket == -1)
                goto lend;

	    if (connect(nsocket, (struct sockaddr *)&dataSocketAddress, sizeof(dataSocketAddress)))
            {
	        ERR("can't connect passive FTP data port.\n");
                closesocket(nsocket);
	        goto lend;
            }
	    lpwfs->pasvSocket = nsocket;
            bSuccess = TRUE;
	}
        else
            FTP_SetResponseError(nResCode);
    }

lend:
    return bSuccess;
}