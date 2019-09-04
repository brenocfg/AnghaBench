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
struct set_name_fn {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ,char const*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  TEST_error (char*,char*) ; 
 scalar_t__ is_exception (char*) ; 

__attribute__((used)) static int check_message(const struct set_name_fn *fn, const char *op,
                         const char *nameincert, int match, const char *name)
{
    char msg[1024];

    if (match < 0)
        return 1;
    BIO_snprintf(msg, sizeof(msg), "%s: %s: [%s] %s [%s]",
                 fn->name, op, nameincert,
                 match ? "matches" : "does not match", name);
    if (is_exception(msg))
        return 1;
    TEST_error("%s", msg);
    return 0;
}