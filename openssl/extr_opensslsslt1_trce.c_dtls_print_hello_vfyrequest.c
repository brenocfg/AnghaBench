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
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_version (int /*<<< orphan*/ *,int,char*,unsigned char const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtls_print_hello_vfyrequest(BIO *bio, int indent,
                                       const unsigned char *msg, size_t msglen)
{
    if (!ssl_print_version(bio, indent, "server_version", &msg, &msglen, NULL))
        return 0;
    if (!ssl_print_hexbuf(bio, indent, "cookie", 1, &msg, &msglen))
        return 0;
    return 1;
}