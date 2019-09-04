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
 unsigned int CUSTOM_EXT_TYPE_2 ; 
 int /*<<< orphan*/  custom_ext_cli_string ; 
 int custom_ext_error ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int custom_ext_2_srv_parse_cb(SSL *s, unsigned int ext_type,
                                     const unsigned char *in,
                                     size_t inlen, int *al, void *arg)
{
    if (ext_type != CUSTOM_EXT_TYPE_2)
        custom_ext_error = 1;
    /* Check for "abc" */
    if (inlen != strlen(custom_ext_cli_string))
        custom_ext_error = 1;
    if (memcmp(in, custom_ext_cli_string, inlen) != 0)
        custom_ext_error = 1;
    return 1;
}