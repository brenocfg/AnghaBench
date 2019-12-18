#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {TYPE_2__ s_un; TYPE_1__ sa; } ;
typedef  TYPE_3__ BIO_ADDR ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 char* OPENSSL_strdup (int /*<<< orphan*/ ) ; 

char *BIO_ADDR_path_string(const BIO_ADDR *ap)
{
#ifdef AF_UNIX
    if (ap->sa.sa_family == AF_UNIX)
        return OPENSSL_strdup(ap->s_un.sun_path);
#endif
    return NULL;
}