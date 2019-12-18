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
typedef  int ULONG ;
struct TYPE_3__ {int Mask; } ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  TYPE_1__* PACCESS_ALLOWED_ACE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GetAllowedWorldAce (int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int UF_ACCOUNTDISABLE ; 
 int UF_DONT_EXPIRE_PASSWD ; 
 int UF_HOMEDIR_REQUIRED ; 
 int UF_INTERDOMAIN_TRUST_ACCOUNT ; 
 int UF_LOCKOUT ; 
 int UF_NORMAL_ACCOUNT ; 
 int UF_PASSWD_CANT_CHANGE ; 
 int UF_PASSWD_NOTREQD ; 
 int UF_SCRIPT ; 
 int UF_SERVER_TRUST_ACCOUNT ; 
 int UF_TEMP_DUPLICATE_ACCOUNT ; 
 int UF_WORKSTATION_TRUST_ACCOUNT ; 
 int USER_ACCOUNT_AUTO_LOCKED ; 
 int USER_ACCOUNT_DISABLED ; 
 int USER_CHANGE_PASSWORD ; 
 int USER_DONT_EXPIRE_PASSWORD ; 
 int USER_HOME_DIRECTORY_REQUIRED ; 
 int USER_INTERDOMAIN_TRUST_ACCOUNT ; 
 int USER_NORMAL_ACCOUNT ; 
 int USER_PASSWORD_NOT_REQUIRED ; 
 int USER_SERVER_TRUST_ACCOUNT ; 
 int USER_TEMP_DUPLICATE_ACCOUNT ; 
 int USER_WORKSTATION_TRUST_ACCOUNT ; 

__attribute__((used)) static
ULONG
GetAccountFlags(ULONG AccountControl,
                PACL Dacl)
{
    PACCESS_ALLOWED_ACE Ace = NULL;
    ULONG Flags = UF_SCRIPT;
    NTSTATUS Status;

    if (Dacl != NULL)
    {
        Status = GetAllowedWorldAce(Dacl, &Ace);
        if (NT_SUCCESS(Status))
        {
            if (Ace == NULL)
            {
                Flags |= UF_PASSWD_CANT_CHANGE;
            }
            else if ((Ace->Mask & USER_CHANGE_PASSWORD) == 0)
            {
                Flags |= UF_PASSWD_CANT_CHANGE;
            }
        }
    }

    if (AccountControl & USER_ACCOUNT_DISABLED)
        Flags |= UF_ACCOUNTDISABLE;

    if (AccountControl & USER_HOME_DIRECTORY_REQUIRED)
        Flags |= UF_HOMEDIR_REQUIRED;

    if (AccountControl & USER_PASSWORD_NOT_REQUIRED)
        Flags |= UF_PASSWD_NOTREQD;

    if (AccountControl & USER_ACCOUNT_AUTO_LOCKED)
        Flags |= UF_LOCKOUT;

    if (AccountControl & USER_DONT_EXPIRE_PASSWORD)
        Flags |= UF_DONT_EXPIRE_PASSWD;

/*
    if (AccountControl & USER_ENCRYPTED_TEXT_PASSWORD_ALLOWED)
        Flags |= UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED;

    if (AccountControl & USER_SMARTCARD_REQUIRED)
        Flags |= UF_SMARTCARD_REQUIRED;

    if (AccountControl & USER_TRUSTED_FOR_DELEGATION)
        Flags |= UF_TRUSTED_FOR_DELEGATION;

    if (AccountControl & USER_NOT_DELEGATED)
        Flags |= UF_NOT_DELEGATED;

    if (AccountControl & USER_USE_DES_KEY_ONLY)
        Flags |= UF_USE_DES_KEY_ONLY;

    if (AccountControl & USER_DONT_REQUIRE_PREAUTH)
        Flags |= UF_DONT_REQUIRE_PREAUTH;

    if (AccountControl & USER_PASSWORD_EXPIRED)
        Flags |= UF_PASSWORD_EXPIRED;
*/

    /* Set account type flags */
    if (AccountControl & USER_TEMP_DUPLICATE_ACCOUNT)
        Flags |= UF_TEMP_DUPLICATE_ACCOUNT;
    else if (AccountControl & USER_NORMAL_ACCOUNT)
        Flags |= UF_NORMAL_ACCOUNT;
    else if (AccountControl & USER_INTERDOMAIN_TRUST_ACCOUNT)
        Flags |= UF_INTERDOMAIN_TRUST_ACCOUNT;
    else if (AccountControl & USER_WORKSTATION_TRUST_ACCOUNT)
        Flags |= UF_WORKSTATION_TRUST_ACCOUNT;
    else if (AccountControl & USER_SERVER_TRUST_ACCOUNT)
        Flags |= UF_SERVER_TRUST_ACCOUNT;

    return Flags;
}