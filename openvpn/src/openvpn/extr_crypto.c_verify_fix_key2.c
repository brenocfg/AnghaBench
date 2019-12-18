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
struct key_type {int dummy; } ;
struct key2 {int n; int /*<<< orphan*/ * keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  check_key (int /*<<< orphan*/ *,struct key_type const*) ; 
 int /*<<< orphan*/  fixup_key (int /*<<< orphan*/ *,struct key_type const*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int,char const*) ; 

void
verify_fix_key2(struct key2 *key2, const struct key_type *kt, const char *shared_secret_file)
{
    int i;

    for (i = 0; i < key2->n; ++i)
    {
        /* Fix parity for DES keys and make sure not a weak key */
        fixup_key(&key2->keys[i], kt);

        /* This should be a very improbable failure */
        if (!check_key(&key2->keys[i], kt))
        {
            msg(M_FATAL, "Key #%d in '%s' is bad.  Try making a new key with --genkey.",
                i+1, shared_secret_file);
        }
    }
}