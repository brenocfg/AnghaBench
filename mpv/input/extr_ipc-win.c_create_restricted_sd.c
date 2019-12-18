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
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertStringSecurityDescriptorToSecurityDescriptorA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  SDDL_REVISION_1 ; 
 char* get_integrity_sid () ; 
 char* get_user_sid () ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static PSECURITY_DESCRIPTOR create_restricted_sd(void)
{
    char *user_sid = get_user_sid();
    char *integrity_sid = get_integrity_sid();
    if (!user_sid || !integrity_sid)
        return NULL;

    char *sddl = talloc_asprintf(NULL,
        "O:%s"                 // Set the owner to user_sid
        "D:(A;;GRGW;;;%s)"     // Grant GENERIC_{READ,WRITE} access to user_sid
        "S:(ML;;NRNWNX;;;%s)", // Disallow read, write and execute permissions
                               // to integrity levels below integrity_sid
        user_sid, user_sid, integrity_sid);
    LocalFree(user_sid);
    LocalFree(integrity_sid);

    PSECURITY_DESCRIPTOR sd = NULL;
    ConvertStringSecurityDescriptorToSecurityDescriptorA(sddl, SDDL_REVISION_1,
        &sd, NULL);
    talloc_free(sddl);

    return sd;
}