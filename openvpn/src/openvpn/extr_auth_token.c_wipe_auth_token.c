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
struct tls_multi {int /*<<< orphan*/ * auth_token_initial; int /*<<< orphan*/ * auth_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secure_memzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

void
wipe_auth_token(struct tls_multi *multi)
{
    if (multi)
    {
        if (multi->auth_token)
        {
            secure_memzero(multi->auth_token, strlen(multi->auth_token));
            free(multi->auth_token);
        }
        if (multi->auth_token_initial)
        {
            secure_memzero(multi->auth_token_initial,
                           strlen(multi->auth_token_initial));
            free(multi->auth_token_initial);
        }
        multi->auth_token = NULL;
        multi->auth_token_initial = NULL;
    }
}