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
struct user_pass {char* password; char* response; int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int plugin_base64_decode (char*,char*,int) ; 
 int /*<<< orphan*/  plugin_secure_memzero (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int const) ; 

__attribute__((used)) static void
split_scrv1_password(struct user_pass *up)
{
    const int skip = strlen("SCRV1:");
    if (strncmp(up->password, "SCRV1:", skip) != 0)
    {
        return;
    }

    char *tmp = strdup(up->password);
    if (!tmp)
    {
        fprintf(stderr, "AUTH-PAM: out of memory parsing static challenge password\n");
        goto out;
    }

    char *pass = tmp + skip;
    char *resp = strchr(pass, ':');
    if (!resp) /* string not in SCRV1:xx:yy format */
    {
        goto out;
    }
    *resp++ = '\0';

    int n = plugin_base64_decode(pass, up->password, sizeof(up->password)-1);
    if (n >= 0)
    {
        up->password[n] = '\0';
        n = plugin_base64_decode(resp, up->response, sizeof(up->response)-1);
        if (n >= 0)
        {
            up->response[n] = '\0';
            if (DEBUG(up->verb))
            {
                fprintf(stderr, "AUTH-PAM: BACKGROUND: parsed static challenge password\n");
            }
            goto out;
        }
    }

    /* decode error: reinstate original value of up->password and return */
    plugin_secure_memzero(up->password, sizeof(up->password));
    plugin_secure_memzero(up->response, sizeof(up->response));
    strcpy(up->password, tmp); /* tmp is guaranteed to fit in up->password */

    fprintf(stderr, "AUTH-PAM: base64 decode error while parsing static challenge password\n");

out:
    if (tmp)
    {
        plugin_secure_memzero(tmp, strlen(tmp));
        free(tmp);
    }
}