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
typedef  int /*<<< orphan*/  up ;
struct user_pass {int verb; char* username; char* password; char* common_name; char* response; struct name_value_list const* name_value_list; } ;
struct name_value_list {int dummy; } ;

/* Variables and functions */
#define  COMMAND_EXIT 129 
#define  COMMAND_VERIFY 128 
 scalar_t__ DEBUG (int) ; 
 int /*<<< orphan*/  RESPONSE_INIT_FAILED ; 
 int /*<<< orphan*/  RESPONSE_INIT_SUCCEEDED ; 
 int /*<<< orphan*/  RESPONSE_VERIFY_FAILED ; 
 int /*<<< orphan*/  RESPONSE_VERIFY_SUCCEEDED ; 
 int /*<<< orphan*/  dlclose_pam () ; 
 char* dlerror () ; 
 int /*<<< orphan*/  dlopen_pam (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct user_pass*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pam_auth (char const*,struct user_pass*) ; 
 int /*<<< orphan*/  plugin_secure_memzero (char*,int) ; 
 int recv_control (int) ; 
 int recv_string (int,char*,int) ; 
 int send_control (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_scrv1_password (struct user_pass*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
pam_server(int fd, const char *service, int verb, const struct name_value_list *name_value_list)
{
    struct user_pass up;
    int command;
#ifdef USE_PAM_DLOPEN
    static const char pam_so[] = "libpam.so";
#endif

    /*
     * Do initialization
     */
    if (DEBUG(verb))
    {
        fprintf(stderr, "AUTH-PAM: BACKGROUND: INIT service='%s'\n", service);
    }

#ifdef USE_PAM_DLOPEN
    /*
     * Load PAM shared object
     */
    if (!dlopen_pam(pam_so))
    {
        fprintf(stderr, "AUTH-PAM: BACKGROUND: could not load PAM lib %s: %s\n", pam_so, dlerror());
        send_control(fd, RESPONSE_INIT_FAILED);
        goto done;
    }
#endif

    /*
     * Tell foreground that we initialized successfully
     */
    if (send_control(fd, RESPONSE_INIT_SUCCEEDED) == -1)
    {
        fprintf(stderr, "AUTH-PAM: BACKGROUND: write error on response socket [1]\n");
        goto done;
    }

    /*
     * Event loop
     */
    while (1)
    {
        memset(&up, 0, sizeof(up));
        up.verb = verb;
        up.name_value_list = name_value_list;

        /* get a command from foreground process */
        command = recv_control(fd);

        if (DEBUG(verb))
        {
            fprintf(stderr, "AUTH-PAM: BACKGROUND: received command code: %d\n", command);
        }

        switch (command)
        {
            case COMMAND_VERIFY:
                if (recv_string(fd, up.username, sizeof(up.username)) == -1
                    || recv_string(fd, up.password, sizeof(up.password)) == -1
                    || recv_string(fd, up.common_name, sizeof(up.common_name)) == -1)
                {
                    fprintf(stderr, "AUTH-PAM: BACKGROUND: read error on command channel: code=%d, exiting\n",
                            command);
                    goto done;
                }

                if (DEBUG(verb))
                {
#if 0
                    fprintf(stderr, "AUTH-PAM: BACKGROUND: USER/PASS: %s/%s\n",
                            up.username, up.password);
#else
                    fprintf(stderr, "AUTH-PAM: BACKGROUND: USER: %s\n", up.username);
#endif
                }

                /* If password is of the form SCRV1:base64:base64 split it up */
                split_scrv1_password(&up);

                if (pam_auth(service, &up)) /* Succeeded */
                {
                    if (send_control(fd, RESPONSE_VERIFY_SUCCEEDED) == -1)
                    {
                        fprintf(stderr, "AUTH-PAM: BACKGROUND: write error on response socket [2]\n");
                        goto done;
                    }
                }
                else /* Failed */
                {
                    if (send_control(fd, RESPONSE_VERIFY_FAILED) == -1)
                    {
                        fprintf(stderr, "AUTH-PAM: BACKGROUND: write error on response socket [3]\n");
                        goto done;
                    }
                }
                plugin_secure_memzero(up.password, sizeof(up.password));
                break;

            case COMMAND_EXIT:
                goto done;

            case -1:
                fprintf(stderr, "AUTH-PAM: BACKGROUND: read error on command channel\n");
                goto done;

            default:
                fprintf(stderr, "AUTH-PAM: BACKGROUND: unknown command code: code=%d, exiting\n",
                        command);
                goto done;
        }
        plugin_secure_memzero(up.response, sizeof(up.response));
    }
done:
    plugin_secure_memzero(up.password, sizeof(up.password));
    plugin_secure_memzero(up.response, sizeof(up.response));
#ifdef USE_PAM_DLOPEN
    dlclose_pam();
#endif
    if (DEBUG(verb))
    {
        fprintf(stderr, "AUTH-PAM: BACKGROUND: EXIT\n");
    }

    return;
}