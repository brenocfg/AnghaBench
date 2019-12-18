#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_multi {TYPE_2__* session; } ;
struct TYPE_4__ {TYPE_1__* key; } ;
struct TYPE_3__ {int authenticated; } ;

/* Variables and functions */
 int KS_SIZE ; 
 int TM_SIZE ; 
 int /*<<< orphan*/  wipe_auth_token (struct tls_multi*) ; 

__attribute__((used)) static void
tls_deauthenticate(struct tls_multi *multi)
{
    if (multi)
    {
        wipe_auth_token(multi);
        for (int i = 0; i < TM_SIZE; ++i)
        {
            for (int j = 0; j < KS_SIZE; ++j)
            {
                multi->session[i].key[j].authenticated = false;
            }
        }
    }
}