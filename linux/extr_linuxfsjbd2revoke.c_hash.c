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
struct TYPE_5__ {TYPE_1__* j_revoke; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_4__ {int /*<<< orphan*/  hash_shift; } ;

/* Variables and functions */
 int hash_64 (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hash(journal_t *journal, unsigned long long block)
{
	return hash_64(block, journal->j_revoke->hash_shift);
}