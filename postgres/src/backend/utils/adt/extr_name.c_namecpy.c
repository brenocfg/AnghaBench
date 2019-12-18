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
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  const* Name ;

/* Variables and functions */
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
namecpy(Name n1, const NameData *n2)
{
	if (!n1 || !n2)
		return -1;
	StrNCpy(NameStr(*n1), NameStr(*n2), NAMEDATALEN);
	return 0;
}