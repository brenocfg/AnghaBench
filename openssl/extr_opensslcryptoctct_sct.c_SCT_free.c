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
struct TYPE_4__ {struct TYPE_4__* sct; struct TYPE_4__* sig; struct TYPE_4__* ext; struct TYPE_4__* log_id; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void SCT_free(SCT *sct)
{
    if (sct == NULL)
        return;

    OPENSSL_free(sct->log_id);
    OPENSSL_free(sct->ext);
    OPENSSL_free(sct->sig);
    OPENSSL_free(sct->sct);
    OPENSSL_free(sct);
}