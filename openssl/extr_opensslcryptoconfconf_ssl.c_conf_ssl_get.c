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
struct TYPE_2__ {char* name; size_t cmd_count; int /*<<< orphan*/  const* cmds; } ;
typedef  int /*<<< orphan*/  SSL_CONF_CMD ;

/* Variables and functions */
 TYPE_1__* ssl_names ; 

const SSL_CONF_CMD *conf_ssl_get(size_t idx, const char **name, size_t *cnt)
{
    *name = ssl_names[idx].name;
    *cnt = ssl_names[idx].cmd_count;
    return ssl_names[idx].cmds;
}