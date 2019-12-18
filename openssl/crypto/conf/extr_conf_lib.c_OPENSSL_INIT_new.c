#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ OPENSSL_INIT_SETTINGS ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CONF_MFLAGS ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

OPENSSL_INIT_SETTINGS *OPENSSL_INIT_new(void)
{
    OPENSSL_INIT_SETTINGS *ret = malloc(sizeof(*ret));

    if (ret == NULL)
        return NULL;

    memset(ret, 0, sizeof(*ret));
    ret->flags = DEFAULT_CONF_MFLAGS;

    return ret;
}