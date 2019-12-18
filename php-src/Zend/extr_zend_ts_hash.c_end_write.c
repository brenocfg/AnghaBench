#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mx_writer; } ;
typedef  TYPE_1__ TsHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  tsrm_mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_write(TsHashTable *ht)
{
#ifdef ZTS
	tsrm_mutex_unlock(ht->mx_writer);
#endif
}