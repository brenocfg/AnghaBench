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
struct TYPE_2__ {int /*<<< orphan*/  add_arg; int /*<<< orphan*/  (* free_cb ) (int /*<<< orphan*/ *,unsigned int,unsigned char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ custom_ext_add_cb_wrap ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned int,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void custom_ext_free_old_cb_wrap(SSL *s, unsigned int ext_type,
                                        unsigned int context,
                                        const unsigned char *out, void *add_arg)
{
    custom_ext_add_cb_wrap *add_cb_wrap = (custom_ext_add_cb_wrap *)add_arg;

    if (add_cb_wrap->free_cb == NULL)
        return;

    add_cb_wrap->free_cb(s, ext_type, out, add_cb_wrap->add_arg);
}