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
struct argv {int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 struct argv argv_clone (struct argv const*,int) ; 
 int /*<<< orphan*/  string_alloc (char const*,int /*<<< orphan*/ *) ; 

struct argv
argv_insert_head(const struct argv *a, const char *head)
{
    struct argv r;
    r = argv_clone(a, 1);
    r.argv[0] = string_alloc(head, NULL);
    return r;
}