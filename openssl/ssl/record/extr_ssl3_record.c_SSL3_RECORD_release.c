#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * comp; } ;
typedef  TYPE_1__ SSL3_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

void SSL3_RECORD_release(SSL3_RECORD *r, size_t num_recs)
{
    size_t i;

    for (i = 0; i < num_recs; i++) {
        OPENSSL_free(r[i].comp);
        r[i].comp = NULL;
    }
}