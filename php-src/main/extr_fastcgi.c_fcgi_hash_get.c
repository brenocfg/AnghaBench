#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int hash_value; unsigned int var_len; unsigned int val_len; char* val; struct TYPE_4__* next; int /*<<< orphan*/  var; } ;
typedef  TYPE_1__ fcgi_hash_bucket ;
struct TYPE_5__ {TYPE_1__** hash_table; } ;
typedef  TYPE_2__ fcgi_hash ;

/* Variables and functions */
 unsigned int FCGI_HASH_TABLE_MASK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static char *fcgi_hash_get(fcgi_hash *h, unsigned int hash_value, char *var, unsigned int var_len, unsigned int *val_len)
{
	unsigned int      idx = hash_value & FCGI_HASH_TABLE_MASK;
	fcgi_hash_bucket *p = h->hash_table[idx];

	while (p != NULL) {
		if (p->hash_value == hash_value &&
		    p->var_len == var_len &&
		    memcmp(p->var, var, var_len) == 0) {
		    *val_len = p->val_len;
		    return p->val;
		}
		p = p->next;
	}
	return NULL;
}