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
typedef  int nIpAddr ;
typedef  int UINT ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  INT ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DoFormatMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ bDoShowNumbers ; 
 scalar_t__ gethostname (char*,int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

PCHAR
GetIpHostName(BOOL Local, UINT IpAddr, CHAR Name[], INT NameLen)
{
//  struct hostent *phostent;
    UINT nIpAddr;

    /* display dotted decimal */
    nIpAddr = htonl(IpAddr);
    if (bDoShowNumbers) {
        sprintf(Name, "%d.%d.%d.%d",
            (nIpAddr >> 24) & 0xFF,
            (nIpAddr >> 16) & 0xFF,
            (nIpAddr >> 8) & 0xFF,
            (nIpAddr) & 0xFF);
        return Name;
    }

    Name[0] = '\0';

    /* try to resolve the name */
    if (!IpAddr) {
        if (!Local) {
            sprintf(Name, "%d.%d.%d.%d",
                (nIpAddr >> 24) & 0xFF,
                (nIpAddr >> 16) & 0xFF,
                (nIpAddr >> 8) & 0xFF,
                (nIpAddr) & 0xFF);
        } else {
            if (gethostname(Name, NameLen) != 0)
                DoFormatMessage(WSAGetLastError());
        }
    } else if (IpAddr == 0x0100007f) {
        if (Local) {
            if (gethostname(Name, NameLen) != 0)
                DoFormatMessage(WSAGetLastError());
        } else {
            strncpy(Name, "localhost", 10);
        }
//  } else if (phostent = gethostbyaddr((char*)&ipaddr, sizeof(nipaddr), PF_INET)) {
//      strcpy(name, phostent->h_name);
    } else {
        sprintf(Name, "%d.%d.%d.%d",
            ((nIpAddr >> 24) & 0x000000FF),
            ((nIpAddr >> 16) & 0x000000FF),
            ((nIpAddr >> 8) & 0x000000FF),
            ((nIpAddr) & 0x000000FF));
    }
    return Name;
}