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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace_free(BIO *channel)
{
    if (channel == NULL)
        return 0;
    OPENSSL_free(BIO_get_data(channel));
    return 1;
}