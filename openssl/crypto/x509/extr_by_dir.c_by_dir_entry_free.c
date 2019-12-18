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
struct TYPE_4__ {int /*<<< orphan*/  hashes; struct TYPE_4__* dir; } ;
typedef  TYPE_1__ BY_DIR_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  by_dir_hash_free ; 
 int /*<<< orphan*/  sk_BY_DIR_HASH_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void by_dir_entry_free(BY_DIR_ENTRY *ent)
{
    OPENSSL_free(ent->dir);
    sk_BY_DIR_HASH_pop_free(ent->hashes, by_dir_hash_free);
    OPENSSL_free(ent);
}