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
typedef  int /*<<< orphan*/  expected_greeting ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  OPENSSL_VERSION_STR ; 

__attribute__((used)) static const char *expected_greeting1(const char *name)
{
    static char expected_greeting[256] = "";

    BIO_snprintf(expected_greeting, sizeof(expected_greeting),
                 "Hello OpenSSL %.20s, greetings from %s!",
                 OPENSSL_VERSION_STR, name);

    return expected_greeting;
}