#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_pass {char* username; TYPE_1__* name_value_list; } ;
struct pam_conv {void* appdata_ptr; int /*<<< orphan*/  conv; } ;
typedef  int /*<<< orphan*/  pam_handle_t ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  my_conv ; 
 int pam_acct_mgmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pam_authenticate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pam_end (int /*<<< orphan*/ *,int) ; 
 int pam_start (char const*,char*,struct pam_conv*,int /*<<< orphan*/ **) ; 
 char* pam_strerror (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
pam_auth(const char *service, const struct user_pass *up)
{
    struct pam_conv conv;
    pam_handle_t *pamh = NULL;
    int status = PAM_SUCCESS;
    int ret = 0;
    const int name_value_list_provided = (up->name_value_list && up->name_value_list->len > 0);

    /* Initialize PAM */
    conv.conv = my_conv;
    conv.appdata_ptr = (void *)up;
    status = pam_start(service, name_value_list_provided ? NULL : up->username, &conv, &pamh);
    if (status == PAM_SUCCESS)
    {
        /* Call PAM to verify username/password */
        status = pam_authenticate(pamh, 0);
        if (status == PAM_SUCCESS)
        {
            status = pam_acct_mgmt(pamh, 0);
        }
        if (status == PAM_SUCCESS)
        {
            ret = 1;
        }

        /* Output error message if failed */
        if (!ret)
        {
            fprintf(stderr, "AUTH-PAM: BACKGROUND: user '%s' failed to authenticate: %s\n",
                    up->username,
                    pam_strerror(pamh, status));
        }

        /* Close PAM */
        pam_end(pamh, status);
    }

    return ret;
}