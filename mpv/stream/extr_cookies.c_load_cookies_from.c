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
struct mp_log {int dummy; } ;
struct cookie_list_type {int secure; struct cookie_list_type* next; void* domain; void* path; void* value; void* name; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 void* col_dup (struct cookie_list_type*,char*) ; 
 int /*<<< orphan*/  cookie_list_t ; 
 int /*<<< orphan*/  free (char*) ; 
 char* load_file (struct mp_log*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_line (char**,char**) ; 
 struct cookie_list_type* talloc_zero (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cookie_list_type *load_cookies_from(void *ctx,
                                                  struct mp_log *log,
                                                  const char *filename)
{
    char *ptr, *file;
    int64_t length;

    ptr = file = load_file(log, filename, &length);
    if (!ptr)
        return NULL;

    struct cookie_list_type *list = NULL;
    while (*ptr) {
        char *cols[7];
        if (parse_line(&ptr, cols)) {
            struct cookie_list_type *new;
            new = talloc_zero(ctx, cookie_list_t);
            new->name = col_dup(new, cols[5]);
            new->value = col_dup(new, cols[6]);
            new->path = col_dup(new, cols[2]);
            new->domain = col_dup(new, cols[0]);
            new->secure = (*(cols[3]) == 't') || (*(cols[3]) == 'T');
            new->next = list;
            list = new;
        }
    }
    free(file);
    return list;
}