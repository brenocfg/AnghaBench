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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ENGINE_get_first () ; 
 int /*<<< orphan*/  ENGINE_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_out ; 

__attribute__((used)) static void list_engines(void)
{
#ifndef OPENSSL_NO_ENGINE
    ENGINE *e;

    BIO_puts(bio_out, "Engines:\n");
    e = ENGINE_get_first();
    while (e) {
        BIO_printf(bio_out, "%s\n", ENGINE_get_id(e));
        e = ENGINE_get_next(e);
    }
#else
    BIO_puts(bio_out, "Engine support is disabled.\n");
#endif
}