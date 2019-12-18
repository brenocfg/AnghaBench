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
 unsigned int CUSTOM_EXT_TYPE_1 ; 
 scalar_t__ custom_ext_cli_string ; 
 int custom_ext_error ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static int custom_ext_1_cli_add_cb(SSL *s, unsigned int ext_type,
                                   const unsigned char **out,
                                   size_t *outlen, int *al, void *arg)
{
    if (ext_type != CUSTOM_EXT_TYPE_1)
        custom_ext_error = 1;
    *out = (const unsigned char *)custom_ext_cli_string;
    *outlen = strlen(custom_ext_cli_string);
    return 1;                   /* Send "abc" */
}