#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
struct TYPE_4__ {char* szUserName; } ;
struct TYPE_6__ {TYPE_1__ ServerInfo; } ;
struct TYPE_5__ {TYPE_3__ InetTransport; } ;
typedef  TYPE_2__ POP3Transport ;
typedef  int /*<<< orphan*/  IInternetTransport ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InternetTransport_DoCommand (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP3Transport_CallbackRecvUSERResp ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void POP3Transport_CallbackSendUSERCmd(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    static const char user[] = "USER ";
    POP3Transport *This = (POP3Transport *)iface;
    char *command;
    int len;

    TRACE("\n");

    len = sizeof(user) + strlen(This->InetTransport.ServerInfo.szUserName) + 2; /* "\r\n" */
    command = HeapAlloc(GetProcessHeap(), 0, len);

    strcpy(command, user);
    strcat(command, This->InetTransport.ServerInfo.szUserName);
    strcat(command, "\r\n");
    InternetTransport_DoCommand(&This->InetTransport, command, POP3Transport_CallbackRecvUSERResp);

    HeapFree(GetProcessHeap(), 0, command);
}