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
typedef  int /*<<< orphan*/  val_type ;
typedef  int /*<<< orphan*/  key_type ;
typedef  int /*<<< orphan*/  inifile ;

/* Variables and functions */
 int inifile_delete_replace_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int inifile_replace(inifile *dba, const key_type *key, const val_type *value)
{
	return inifile_delete_replace_append(dba, key, value, 0, NULL);
}