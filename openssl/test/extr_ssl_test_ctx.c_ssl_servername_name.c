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
typedef  int /*<<< orphan*/  ssl_servername_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 char const* enum_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_servername ; 

const char *ssl_servername_name(ssl_servername_t server)
{
    return enum_name(ssl_servername, OSSL_NELEM(ssl_servername),
                     server);
}