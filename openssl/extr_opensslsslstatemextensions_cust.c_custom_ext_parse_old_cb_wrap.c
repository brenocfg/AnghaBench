#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* parse_cb ) (int /*<<< orphan*/ *,unsigned int,unsigned char const*,size_t,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  parse_arg; } ;
typedef  TYPE_1__ custom_ext_parse_cb_wrap ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,unsigned int,unsigned char const*,size_t,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int custom_ext_parse_old_cb_wrap(SSL *s, unsigned int ext_type,
                                        unsigned int context,
                                        const unsigned char *in,
                                        size_t inlen, X509 *x, size_t chainidx,
                                        int *al, void *parse_arg)
{
    custom_ext_parse_cb_wrap *parse_cb_wrap =
        (custom_ext_parse_cb_wrap *)parse_arg;

    if (parse_cb_wrap->parse_cb == NULL)
        return 1;

    return parse_cb_wrap->parse_cb(s, ext_type, in, inlen, al,
                                   parse_cb_wrap->parse_arg);
}