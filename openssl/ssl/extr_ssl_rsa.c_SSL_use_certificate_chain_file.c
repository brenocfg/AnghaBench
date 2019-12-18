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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int use_certificate_chain_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int SSL_use_certificate_chain_file(SSL *ssl, const char *file)
{
    return use_certificate_chain_file(NULL, ssl, file);
}