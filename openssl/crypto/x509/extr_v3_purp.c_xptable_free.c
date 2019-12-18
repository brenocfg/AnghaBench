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
struct TYPE_4__ {int flags; struct TYPE_4__* sname; struct TYPE_4__* name; } ;
typedef  TYPE_1__ X509_PURPOSE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int X509_PURPOSE_DYNAMIC ; 
 int X509_PURPOSE_DYNAMIC_NAME ; 

__attribute__((used)) static void xptable_free(X509_PURPOSE *p)
{
    if (p == NULL)
        return;
    if (p->flags & X509_PURPOSE_DYNAMIC) {
        if (p->flags & X509_PURPOSE_DYNAMIC_NAME) {
            OPENSSL_free(p->name);
            OPENSSL_free(p->sname);
        }
        OPENSSL_free(p);
    }
}