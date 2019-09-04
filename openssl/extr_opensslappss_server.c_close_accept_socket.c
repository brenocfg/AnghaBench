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

/* Variables and functions */
 int /*<<< orphan*/  BIO_closesocket (scalar_t__) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ accept_socket ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static void close_accept_socket(void)
{
    BIO_printf(bio_err, "shutdown accept socket\n");
    if (accept_socket >= 0) {
        BIO_closesocket(accept_socket);
    }
}