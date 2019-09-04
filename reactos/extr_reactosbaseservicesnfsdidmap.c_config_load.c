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
struct config_pair {int key; char* value; int /*<<< orphan*/  value_len; } ;
struct config_option {scalar_t__ type; int offset; int /*<<< orphan*/  max_len; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ERROR_BUFFER_OVERFLOW ; 
 int ERROR_INVALID_PARAMETER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  StringCchCopyNA (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_INT ; 
 int config_find_option (struct config_pair*,struct config_option const**) ; 
 int config_parse_pair (char*,struct config_pair*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  parse_uint (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_load(
    struct idmap_config *config,
    const char *filename)
{
    char buffer[1024], *pos;
    FILE *file;
    struct config_pair pair;
    const struct config_option *option;
    int line = 0;
    int status = NO_ERROR;

    /* open the file */
    file = fopen(filename, "r");
    if (file == NULL) {
        eprintf("config_load() failed to open file '%s'\n", filename);
        goto out;
    }

    /* read each line */
    while (fgets(buffer, sizeof(buffer), file)) {
        line++;

        /* skip whitespace */
        pos = buffer;
        while (isspace(*pos)) pos++;

        /* skip comments and empty lines */
        if (*pos == '#' || *pos == 0)
            continue;

        /* parse line into a key=value pair */
        status = config_parse_pair(buffer, &pair);
        if (status) {
            eprintf("error on line %d: %s\n", line, buffer);
            break;
        }

        /* find the config_option by key */
        status = config_find_option(&pair, &option);
        if (status) {
            eprintf("unrecognized option '%s' on line %d: %s\n",
                pair.key, line, buffer);
            status = ERROR_INVALID_PARAMETER;
            break;
        }

        if (option->type == TYPE_INT) {
            if (!parse_uint(pair.value, (UINT*)((char*)config + option->offset))) {
                status = ERROR_INVALID_PARAMETER;
                eprintf("expected a number on line %d: %s=\"%s\"\n",
                    line, pair.key, pair.value);
                break;
            }
        } else {
            if (FAILED(StringCchCopyNA((char*)config + option->offset,
                    option->max_len, pair.value, pair.value_len))) {
                status = ERROR_BUFFER_OVERFLOW;
                eprintf("overflow on line %d: %s=\"%s\"\n",
                    line, pair.key, pair.value);
                break;
            }
        }
    }

    fclose(file);
out:
    return status;
}