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
struct idmap_config {int dummy; } ;
struct config_option {int offset; scalar_t__ type; int /*<<< orphan*/  max_len; int /*<<< orphan*/  def; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int ARRAYSIZE (struct config_option*) ; 
 int ERROR_BUFFER_OVERFLOW ; 
 int ERROR_INVALID_PARAMETER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  StringCchCopyA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_INT ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct config_option* g_options ; 
 int /*<<< orphan*/  parse_uint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_defaults(
    struct idmap_config *config)
{
    const struct config_option *option;
    const int count = ARRAYSIZE(g_options);
    char *dst;
    int i, status = NO_ERROR;

    for (i = 0; i < count; i++) {
        option = &g_options[i];
        dst = (char*)config + option->offset;

        if (option->type == TYPE_INT) {
            if (!parse_uint(option->def, (UINT*)dst)) {
                status = ERROR_INVALID_PARAMETER;
                eprintf("failed to parse default value of %s=\"%s\": "
                    "expected a number\n", option->key, option->def);
                break;
            }
        } else {
            if (FAILED(StringCchCopyA(dst, option->max_len, option->def))) {
                status = ERROR_BUFFER_OVERFLOW;
                eprintf("failed to parse default value of %s=\"%s\": "
                    "buffer overflow > %u\n", option->key, option->def,
                    option->max_len);
                break;
            }
        }
    }
    return status;
}