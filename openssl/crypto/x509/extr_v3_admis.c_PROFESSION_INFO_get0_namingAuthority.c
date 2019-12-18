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
struct TYPE_3__ {int /*<<< orphan*/  const* namingAuthority; } ;
typedef  TYPE_1__ PROFESSION_INFO ;
typedef  int /*<<< orphan*/  NAMING_AUTHORITY ;

/* Variables and functions */

const NAMING_AUTHORITY *PROFESSION_INFO_get0_namingAuthority(const PROFESSION_INFO *pi)
{
    return pi->namingAuthority;
}