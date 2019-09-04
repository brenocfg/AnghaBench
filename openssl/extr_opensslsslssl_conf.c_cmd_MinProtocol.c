#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  min_version; } ;
typedef  TYPE_1__ SSL_CONF_CTX ;

/* Variables and functions */
 int min_max_proto (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_MinProtocol(SSL_CONF_CTX *cctx, const char *value)
{
    return min_max_proto(cctx, value, cctx->min_version);
}