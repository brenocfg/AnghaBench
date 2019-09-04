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
typedef  int /*<<< orphan*/  bio_dgram_data ;
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

__attribute__((used)) static int dgram_new(BIO *bi)
{
    bio_dgram_data *data = OPENSSL_zalloc(sizeof(*data));

    if (data == NULL)
        return 0;
    bi->ptr = data;
    return 1;
}