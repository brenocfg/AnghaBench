#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* info; struct TYPE_4__* id; int /*<<< orphan*/  v; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ SRP_user_pwd ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void SRP_user_pwd_free(SRP_user_pwd *user_pwd)
{
    if (user_pwd == NULL)
        return;
    BN_free(user_pwd->s);
    BN_clear_free(user_pwd->v);
    OPENSSL_free(user_pwd->id);
    OPENSSL_free(user_pwd->info);
    OPENSSL_free(user_pwd);
}