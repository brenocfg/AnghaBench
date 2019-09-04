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
 int serverinfoex_srv_add_cb (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned char const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static int serverinfo_srv_add_cb(SSL *s, unsigned int ext_type,
                                 const unsigned char **out, size_t *outlen,
                                 int *al, void *arg)
{
    return serverinfoex_srv_add_cb(s, ext_type, 0, out, outlen, NULL, 0, al,
                                   arg);
}