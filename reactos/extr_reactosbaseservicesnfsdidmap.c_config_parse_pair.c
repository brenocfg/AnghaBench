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
struct config_pair {char* key; int key_len; char* value; int value_len; } ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ isspace (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int config_parse_pair(
    char *line,
    struct config_pair *pair)
{
    char *pos = line;
    int status = NO_ERROR;

    /* terminate at comment */
    pos = strchr(line, '#');
    if (pos) *pos = 0;

    /* skip whitespace before key */
    pos = line;
    while (isspace(*pos)) pos++;
    pair->key = pos;

    pos = strchr(pos, '=');
    if (pos == NULL) {
        eprintf("missing '='\n");
        status = ERROR_INVALID_PARAMETER;
        goto out;
    }

    /* skip whitespace after key */
    pair->key_len = pos - pair->key;
    while (pair->key_len && isspace(pair->key[pair->key_len-1]))
        pair->key_len--;

    if (pair->key_len <= 0) {
        eprintf("empty key\n");
        status = ERROR_INVALID_PARAMETER;
        goto out;
    }

    /* skip whitespace after = */
    pos++;
    while (isspace(*pos)) pos++;

    if (*pos == 0) {
        eprintf("end of line looking for value\n");
        status = ERROR_INVALID_PARAMETER;
        goto out;
    }

    if (*pos == '\"') {
        /* value is between the "s */
        pair->value = pos + 1;
        pos = strchr(pair->value, '\"');
        if (pos == NULL) {
            eprintf("no matching '\"'\n");
            status = ERROR_INVALID_PARAMETER;
            goto out;
        }
        pair->value_len = pos - pair->value;
    } else {
        pair->value = pos;
        pair->value_len = strlen(pair->value);

        /* skip whitespace after value */
        while (pair->value_len && isspace(pair->value[pair->value_len-1]))
            pair->value_len--;
    }

    /* on success, null terminate the key and value */
    ((char*)pair->key)[pair->key_len] = 0;
    ((char*)pair->value)[pair->value_len] = 0;
out:
    return status;
}