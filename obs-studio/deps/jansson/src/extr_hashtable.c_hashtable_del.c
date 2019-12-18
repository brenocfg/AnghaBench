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
typedef  int /*<<< orphan*/  hashtable_t ;

/* Variables and functions */
 size_t hash_str (char const*) ; 
 int hashtable_do_del (int /*<<< orphan*/ *,char const*,size_t) ; 

int hashtable_del(hashtable_t *hashtable, const char *key)
{
    size_t hash = hash_str(key);
    return hashtable_do_del(hashtable, key, hash);
}