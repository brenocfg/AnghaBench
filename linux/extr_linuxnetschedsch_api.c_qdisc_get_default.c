#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 TYPE_1__* default_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_mod_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

void qdisc_get_default(char *name, size_t len)
{
	read_lock(&qdisc_mod_lock);
	strlcpy(name, default_qdisc_ops->id, len);
	read_unlock(&qdisc_mod_lock);
}