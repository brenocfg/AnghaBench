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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int SSL_ctrl (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int protocol_from_string (char const*) ; 

__attribute__((used)) static int set_protocol_version(const char *version, SSL *ssl, int setting)
{
    if (version != NULL) {
        int ver = protocol_from_string(version);
        if (ver < 0) {
            BIO_printf(bio_err, "Error parsing: %s\n", version);
            return 0;
        }
        return SSL_ctrl(ssl, setting, ver, NULL);
    }
    return 1;
}