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
struct idmap_lookup {int type; size_t klass; size_t attr; int /*<<< orphan*/  value; } ;
struct idmap_config {int /*<<< orphan*/ * attributes; int /*<<< orphan*/ * classes; } ;
typedef  int /*<<< orphan*/  UINT_PTR ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int ERROR_BUFFER_OVERFLOW ; 
 int ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  StringCchPrintfA (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TYPE_INT 129 
#define  TYPE_STR 128 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idmap_filter(
    struct idmap_config *config,
    const struct idmap_lookup *lookup,
    char *filter,
    size_t filter_len)
{
    UINT_PTR i;
    int status = NO_ERROR;

    switch (lookup->type) {
    case TYPE_INT:
        i = (UINT_PTR)lookup->value;
        if (FAILED(StringCchPrintfA(filter, filter_len,
                "(&(objectClass=%s)(%s=%u))",
                config->classes[lookup->klass],
                config->attributes[lookup->attr], (UINT)i))) {
            status = ERROR_BUFFER_OVERFLOW;
            eprintf("ldap filter buffer overflow: '%s=%u'\n",
                config->attributes[lookup->attr], (UINT)i);
        }
        break;

    case TYPE_STR:
        if (FAILED(StringCchPrintfA(filter, filter_len,
                "(&(objectClass=%s)(%s=%s))",
                config->classes[lookup->klass],
                config->attributes[lookup->attr], lookup->value))) {
            status = ERROR_BUFFER_OVERFLOW;
            eprintf("ldap filter buffer overflow: '%s=%s'\n",
                config->attributes[lookup->attr], lookup->value);
        }
        break;

    default:
        status = ERROR_INVALID_PARAMETER;
        break;
    }
    return status;
}