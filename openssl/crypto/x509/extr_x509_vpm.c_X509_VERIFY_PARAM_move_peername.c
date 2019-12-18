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
struct TYPE_4__ {char* peername; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (char*) ; 

void X509_VERIFY_PARAM_move_peername(X509_VERIFY_PARAM *to,
                                     X509_VERIFY_PARAM *from)
{
    char *peername = (from != NULL) ? from->peername : NULL;

    if (to->peername != peername) {
        OPENSSL_free(to->peername);
        to->peername = peername;
    }
    if (from)
        from->peername = NULL;
}