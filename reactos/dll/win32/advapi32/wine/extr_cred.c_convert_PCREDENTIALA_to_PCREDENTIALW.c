#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {scalar_t__ UserName; scalar_t__ TargetAlias; int /*<<< orphan*/  Persist; scalar_t__ CredentialBlobSize; int /*<<< orphan*/  CredentialBlob; int /*<<< orphan*/  LastWritten; scalar_t__ Comment; scalar_t__ TargetName; int /*<<< orphan*/  Type; int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * UserName; int /*<<< orphan*/ * TargetAlias; int /*<<< orphan*/ * Attributes; scalar_t__ AttributeCount; int /*<<< orphan*/  Persist; int /*<<< orphan*/ * CredentialBlob; scalar_t__ CredentialBlobSize; int /*<<< orphan*/  LastWritten; int /*<<< orphan*/ * Comment; int /*<<< orphan*/ * TargetName; int /*<<< orphan*/  Type; int /*<<< orphan*/  Flags; } ;
typedef  TYPE_1__* PCREDENTIALW ;
typedef  void* LPWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  CREDENTIALW ;
typedef  TYPE_2__ CREDENTIALA ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static INT convert_PCREDENTIALA_to_PCREDENTIALW(const CREDENTIALA *CredentialA, PCREDENTIALW CredentialW, INT len)
{
    char *buffer;
    INT string_len;
    INT needed = sizeof(CREDENTIALW);

    if (!CredentialW)
    {
        if (CredentialA->TargetName)
            needed += sizeof(WCHAR) * MultiByteToWideChar(CP_ACP, 0, CredentialA->TargetName, -1, NULL, 0);
        if (CredentialA->Comment)
            needed += sizeof(WCHAR) * MultiByteToWideChar(CP_ACP, 0, CredentialA->Comment, -1, NULL, 0);
        needed += CredentialA->CredentialBlobSize;
        if (CredentialA->TargetAlias)
            needed += sizeof(WCHAR) * MultiByteToWideChar(CP_ACP, 0, CredentialA->TargetAlias, -1, NULL, 0);
        if (CredentialA->UserName)
            needed += sizeof(WCHAR) * MultiByteToWideChar(CP_ACP, 0, CredentialA->UserName, -1, NULL, 0);

        return needed;
    }

    buffer = (char *)CredentialW + sizeof(CREDENTIALW);
    len -= sizeof(CREDENTIALW);
    CredentialW->Flags = CredentialA->Flags;
    CredentialW->Type = CredentialA->Type;
    if (CredentialA->TargetName)
    {
        CredentialW->TargetName = (LPWSTR)buffer;
        string_len = MultiByteToWideChar(CP_ACP, 0, CredentialA->TargetName, -1, CredentialW->TargetName, len / sizeof(WCHAR));
        buffer += sizeof(WCHAR) * string_len;
        needed += sizeof(WCHAR) * string_len;
        len -= sizeof(WCHAR) * string_len;
    }
    else
        CredentialW->TargetName = NULL;
    if (CredentialA->Comment)
    {
        CredentialW->Comment = (LPWSTR)buffer;
        string_len = MultiByteToWideChar(CP_ACP, 0, CredentialA->Comment, -1, CredentialW->Comment, len / sizeof(WCHAR));
        buffer += sizeof(WCHAR) * string_len;
        needed += sizeof(WCHAR) * string_len;
        len -= sizeof(WCHAR) * string_len;
    }
    else
        CredentialW->Comment = NULL;
    CredentialW->LastWritten = CredentialA->LastWritten;
    CredentialW->CredentialBlobSize = CredentialA->CredentialBlobSize;
    if (CredentialA->CredentialBlobSize)
    {
        CredentialW->CredentialBlob =(LPBYTE)buffer;
        memcpy(CredentialW->CredentialBlob, CredentialA->CredentialBlob,
               CredentialA->CredentialBlobSize);
        buffer += CredentialA->CredentialBlobSize;
        needed += CredentialA->CredentialBlobSize;
        len -= CredentialA->CredentialBlobSize;
    }
    else
        CredentialW->CredentialBlob = NULL;
    CredentialW->Persist = CredentialA->Persist;
    CredentialW->AttributeCount = 0;
    CredentialW->Attributes = NULL; /* FIXME */
    if (CredentialA->TargetAlias)
    {
        CredentialW->TargetAlias = (LPWSTR)buffer;
        string_len = MultiByteToWideChar(CP_ACP, 0, CredentialA->TargetAlias, -1, CredentialW->TargetAlias, len / sizeof(WCHAR));
        buffer += sizeof(WCHAR) * string_len;
        needed += sizeof(WCHAR) * string_len;
        len -= sizeof(WCHAR) * string_len;
    }
    else
        CredentialW->TargetAlias = NULL;
    if (CredentialA->UserName)
    {
        CredentialW->UserName = (LPWSTR)buffer;
        string_len = MultiByteToWideChar(CP_ACP, 0, CredentialA->UserName, -1, CredentialW->UserName, len / sizeof(WCHAR));
        needed += sizeof(WCHAR) * string_len;
    }
    else
        CredentialW->UserName = NULL;

    return needed;
}