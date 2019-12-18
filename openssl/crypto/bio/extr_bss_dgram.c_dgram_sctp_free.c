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
typedef  int /*<<< orphan*/  bio_dgram_sctp_data ;
struct TYPE_4__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dgram_clear (TYPE_1__*) ; 

__attribute__((used)) static int dgram_sctp_free(BIO *a)
{
    bio_dgram_sctp_data *data;

    if (a == NULL)
        return 0;
    if (!dgram_clear(a))
        return 0;

    data = (bio_dgram_sctp_data *) a->ptr;
    if (data != NULL)
        OPENSSL_free(data);

    return 1;
}